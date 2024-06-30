#include<iostream>
#include<string>
#include<cstdlib>
#include<orchid/socket.hh>
#include<orchid/marshall.hh>
#include<orchid/utils.hh>

int main() {
	orchid::tcp_streamer sock;
	sock.init();
	sock.connect(1234);
	orchid::utils::set_socket_to_non_block(sock.get_fd());
	std::cout << "fd: " << sock.get_fd() << std::endl;
	while(true) {
		if(-1 == sock.get_runner()) break;
		std::cout << "orchid|> ";
		std::string input;
		std::getline(std::cin, input);
		input = orchid::marshall::marshall_from(input);
		if(-1 == sock.send(sock.get_fd(), input)) continue;
		std::string msg;
		if(-1 == sock.recv(sock.get_fd(), msg)) continue;
		std::cout << "orchid|> " << msg << std::endl;
	}
	std::cout << "here\n";
	sock.close();
	std::exit(0);
}
