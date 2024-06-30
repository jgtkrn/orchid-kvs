#include<iostream>
#include<cstdlib>
#include<string>
#include<orchid/socket.hh>
#include<orchid/event_dispatcher.hh>
#include<orchid/utils.hh>
#include<orchid/marshall.hh>

int main(){
	orchid::tcp_listener sock;
	sock.init();
	sock.listen(1234);
	orchid::utils::set_socket_to_non_block(sock.get_fd());
	orchid::event_dispatcher evd;
	evd.init();
	evd.attach_event(sock.get_fd());
	EFD event_fd;
	while(true){
		if(-1 == sock.get_runner()) break;
		if(-1 == evd.get_runner()) break;
		if(-1 == evd.watch_event()) break;
		for(int i = 0; i < evd.get_nfds(); ++i) {
			event_fd = evd.get_index_efd(i);
			if(event_fd == sock.get_fd()) {
				SOCKET conn = sock.accept();
				if(conn < 0) continue;
				std::cout << "Retrieve connection from fd: " << conn << std::endl;
				orchid::utils::set_socket_to_non_block(conn);
				evd.attach_event(conn);
			} else {
				std::string message;
				int recv_len = sock.recv(event_fd, message);
				std::cout << "recv: " << recv_len << std::endl;
				if(recv_len <= -1) continue;
				if(recv_len == 0) {
					evd.detach_event(event_fd);
					continue;
				};
				if(orchid::marshall::validate_format(message)) {
					struct orchid::marshall::orchid_entry entry = orchid::marshall::unmarshall_from(message);
					std::string ok_res = "OK";
					if(sock.send(event_fd, ok_res) > 0) std::cout << "Failed send response to client..." << std::endl;
					std::cout << "command_length: " << entry.command_length << std::endl;
					std::cout << "command: " << entry.command << std::endl;
					std::cout << "key: " << entry.key << std::endl;
					std::cout << "value: " << entry.value << std::endl;
				} else {
					std::string err_res = "Err: Invalid command format";
					if(-1 == sock.send(event_fd, err_res)) std::cout << "Failed send response to client..." << std::endl;
				}
				std::cout << message << std::endl;
			}
		}
	}
	sock.close();
	evd.close();
	std::exit(0);
}
