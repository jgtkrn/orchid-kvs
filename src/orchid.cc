#include<iostream>
#include<cstdlib>
#include<string>
#include<orchid/socket.hh>
#include<orchid/event_dispatcher.hh>
#include<orchid/utils.hh>
#include<orchid/marshall.hh>
#include<ds/hash_map.hh>
#include<config/generator.hh>

void fail_send() {
 std::cout << "Failed send response to client..." << std::endl;	
}

void handle_stream(orchid::tcp_listener& sock, orchid::event_dispatcher& evd, ds::hash_map& hash_map) {
	orchid::marshall::orchid_entry entry;
	std::string ok_res = "OK";
	std::string nf_res = "Err: Not Found";
	std::string inv_res = "Err: Invalid Format";
	std::string message;
	int recv_len;
	while(sock.get_runner() != -1) {
		if(-1 == evd.get_runner()) break;
		if(-1 == evd.watch_event()) break;
		for(int i = 0; i < evd.get_nfds(); ++i) {
			event_fd = evd.get_index_efd(i);
			if(event_fd == sock.get_fd()) {
				SOCKET conn = sock.accept();
				if(conn < 0) continue;
				orchid::utils::set_socket_to_non_block(conn);
				evd.attach_event(conn);
				continue;
			}
			recv_len = sock.recv(event_fd, message);
			if(recv_len <= -1) continue;
			if(recv_len == 0) {
				evd.detach_event(event_fd);
				continue;
			};
			if(orchid::marshall::validate_format(message)) {
				entry = orchid::marshall::unmarshall_from(message);
				if(entry.command == "SET" || entry.command == "set") {
					hash_map.insert(entry.key, entry.value);
					if(sock.send(event_fd, ok_res) < 0) fail_send();
					continue;
				}
				if(entry.command == "GET" || entry.command == "get") {
					std::string node = hash_map.search(entry.key);
					if(node.size() > 0) {
						if(sock.send(event_fd, node) < 0) fail_send();
						continue;
					} 
					if(sock.send(event_fd, nf_res) < 0) fail_send();
				}
				if(entry.command == "DEL" || entry.command == "del") {
					hash_map.remove(entry.key);
					if(sock.send(event_fd, ok_res) < 0) fail_send();
					continue;
				}
			} else {
				if(-1 == sock.send(event_fd, inv_res)) fail_send();
				continue;
			}
		}
	}
}

int main(int argc, char* argv[]){
	EFD event_fd;

	/**
	 * initiaize configuration
	 */
	std::string conf_file = "orchid.conf";
	config::dictionary cfg;
	if(!config::generate(conf_file, cfg)) {
		std::exit(0);
	}
	config::args_config_server(argc, argv, cfg);
	
	/**
	 * initialize tcp_listener
	 */
	orchid::tcp_listener sock(cfg);
	sock.init();
	sock.listen();
	orchid::utils::set_socket_to_non_block(sock.get_fd());

	/**
	 * initalize event_dispatcher
	 */
	orchid::event_dispatcher evd;
	evd.init();
	
	/**
	 * add tcp_listener socket to event_dispatcher
	 */
	evd.attach_event(sock.get_fd());

	/**
	 * initialize hash_map
	 */
	ds::hash_map hash_map(cfg.hm_cluster_size);

	/**
	 * handle incoming data
	 */
	handle_stream(sock, evd, hash_map);

	sock.close();
	evd.close();
	std::exit(0);
}
