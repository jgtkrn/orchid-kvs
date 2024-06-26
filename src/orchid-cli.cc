#include<iostream>
#include<string>
#include<orchid/socket.hh>

int main() {
	orchid::tcp_streamer sock;
	sock.init();
	sock.connect(1234);
	std::cout << sock.get_fd() << std::endl;
	while(1) {
		if(-1 == sock.get_runner()) break;
		std::cout << "orchid|> ";
		std::string input;
		std::getline(std::cin, input);
		sock.send(sock.get_fd(), input);
	}
	sock.close();
	return 0;
}
