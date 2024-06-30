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
	std::cout << "fd: " << sock.get_fd() << std::endl;
	orchid::utils::set_socket_to_non_block(sock.get_fd());
	orchid::event_dispatcher evd;
	evd.init();
	evd.attach_event(sock.get_fd());
	while(true){
		if(-1 == sock.get_runner()) break;
		if(-1 == evd.get_runner()) break;
		if(-1 == evd.watch_event()) break;
		for(int i = 0; i < evd.get_nfds(); ++i) {
			if(evd.get_index_efd(i) == sock.get_fd()) {
				SOCKET conn = sock.accept();
				if(conn < 0) continue;
				std::cout << "Retrieve connection from fd: " << conn << std::endl;
				orchid::utils::set_socket_to_non_block(conn);
				evd.attach_event(conn);
			} else {
				std::string message;
				if(-1 == sock.recv(evd.get_index_efd(i), message)) continue;
				if(orchid::marshall::validate_format(message)) {
					struct orchid::marshall::orchid_entry entry = orchid::marshall::unmarshall_from(message);
					std::string ok_res = "OK";
					if(-1 == sock.send(evd.get_index_efd(i), ok_res)) std::cout << "Failed send response to client..." << std::endl;
					std::cout << "command_length: " << entry.command_length << std::endl;
					std::cout << "command: " << entry.command << std::endl;
					std::cout << "key: " << entry.key << std::endl;
					std::cout << "value: " << entry.value << std::endl;
				} else {
					std::string err_res = "Err: Invalid command format";
					if(-1 == sock.send(evd.get_index_efd(i), err_res)) std::cout << "Failed send response to client..." << std::endl;
				}
				std::cout << message << std::endl;
			}
		}
	}
	sock.close();
	evd.close();
	std::exit(0);
}
