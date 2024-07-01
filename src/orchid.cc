#include<iostream>
#include<cstdlib>
#include<string>
#include<orchid/socket.hh>
#include<orchid/event_dispatcher.hh>
#include<orchid/utils.hh>
#include<orchid/marshall.hh>
#include<ds/entry_node.hh>
#include<ds/hash_map.hh>

int main(){
	orchid::tcp_listener sock;
	sock.init();
	sock.listen(1234);
	orchid::utils::set_socket_to_non_block(sock.get_fd());
	orchid::event_dispatcher evd;
	evd.init();
	evd.attach_event(sock.get_fd());
	EFD event_fd;
	ds::hash_map hash_map(4);
	while(true){
		if(-1 == sock.get_runner()) break;
		if(-1 == evd.get_runner()) break;
		if(-1 == evd.watch_event()) break;
		for(int i = 0; i < evd.get_nfds(); ++i) {
			event_fd = evd.get_index_efd(i);
			if(event_fd == sock.get_fd()) {
				SOCKET conn = sock.accept();
				if(conn < 0) continue;
				orchid::utils::set_socket_to_non_block(conn);
				evd.attach_event(conn);
			} else {
				std::string message;
				int recv_len = sock.recv(event_fd, message);
				if(recv_len <= -1) continue;
				if(recv_len == 0) {
					evd.detach_event(event_fd);
					continue;
				};
				if(orchid::marshall::validate_format(message)) {
					std::string ok_res = "OK";
					struct orchid::marshall::orchid_entry entry = orchid::marshall::unmarshall_from(message);
					std::cout << "command_length: " << entry.command_length << std::endl;
					std::cout << "command: " << entry.command << std::endl;
					std::cout << "key: " << entry.key << std::endl;
					std::cout << "value: " << entry.value << std::endl;
					if(entry.command == "SET" || entry.command == "set") {
						hash_map.insert(entry.key, entry.value);
						if(sock.send(event_fd, ok_res) < 0) std::cout << "Failed send response to client..." << std::endl;
					}
					if(entry.command == "GET" || entry.command == "get") {
						auto node = hash_map.search(entry.key);
						std::string val = node == nullptr ? "Not Found" : node;
						if(sock.send(event_fd, val) < 0) std::cout << "Failed send response to client..." << std::endl;
					}
					if(entry.command == "DEL" || entry.command == "del") {
						if(sock.send(event_fd, ok_res) < 0) std::cout << "Failed send response to client..." << std::endl;
					}
				} else {
					std::string err_res = "Err: Invalid command format";
					if(-1 == sock.send(event_fd, err_res)) std::cout << "Failed send response to client..." << std::endl;
				}
			}
		}
	}
	sock.close();
	evd.close();
	std::exit(0);
}
