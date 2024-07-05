#include<iostream>
#include<string>
#include<cstdlib>
#include<orchid/socket.hh>
#include<orchid/marshall.hh>
#include<orchid/utils.hh>
#include<config/generator.hh>

void handle_stream(orchid::tcp_streamer& sock) {
	while(sock.get_runner() != -1) {
		std::string msg;
		std::string input;
		int recv_len;
		std::cout << "orchid|> ";
		std::getline(std::cin, input);
		input = orchid::marshall::marshall_from(input);
		if(sock.send(sock.get_fd(), input) < 0) std::cout << "orchid|> Failed send message...\n";
		recv_len = sock.recv(sock.get_fd(), msg);
		if(recv_len <= 0) continue;
		std::cout << "orchid|> " << msg << std::endl;
	}
}

int main(int argc, char* argv[]) {
	/**
	 * initiaize configuration
	 */
	std::string conf_file = "orchid.conf";
	config::dictionary cfg;
	if(!config::generate(conf_file, cfg)) {
		std::exit(0);
	}
	config::args_config_client(argc, argv, cfg);

	/**
	 * initialize tcp_streamer
	 */
	orchid::tcp_streamer sock;
	sock.load_config(cfg);
	sock.init();
	sock.connect();

	/**
	 * handle incoming data
	 */
	handle_stream(sock);

	sock.close();
	std::exit(0);
}
