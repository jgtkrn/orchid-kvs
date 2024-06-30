#include<iostream>
#include<string>
#include<orchid/socket.hh>
#include<orchid/marshall.hh>

int main() {
	orchid::tcp_streamer sock;
	sock.init();
	sock.connect(1234);
	while(1) {
		if(-1 == sock.get_runner()) break;
		std::cout << "orchid|> ";
		std::string input;
		std::getline(std::cin, input);
		input = orchid::marshall::marshall_from(input);
		sock.send(sock.get_fd(), input);
		std::string msg;
		sock.recv(sock.get_fd(), msg);
		std::cout << "orchid|> " << msg << std::endl;
	}
	sock.close();
	return 0;
}
