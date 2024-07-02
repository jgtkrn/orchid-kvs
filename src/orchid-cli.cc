#include<iostream>
#include<string>
#include<cstdlib>
#include<orchid/socket.hh>
#include<orchid/marshall.hh>
#include<orchid/utils.hh>

int main() {
	orchid::tcp_streamer sock;
	sock.init();
	sock.connect();
	while(true) {
		if(-1 == sock.get_runner()) break;
		std::cout << "orchid|> ";
		std::string input;
		std::getline(std::cin, input);
		input = orchid::marshall::marshall_from(input);
		if(sock.send(sock.get_fd(), input) < 0) std::cout << "orchid|> Failed send message...\n";
		std::string msg;
		int recv_len = sock.recv(sock.get_fd(), msg);
		if(recv_len <= 0) continue;
		std::cout << "orchid|> " << msg << std::endl;
	}
	sock.close();
	std::exit(0);
}
