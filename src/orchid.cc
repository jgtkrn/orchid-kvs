#include<iostream>
#include<string>
#include<orchid/socket.hh>

int main(){
	orchid::tcp_listener sock;
	sock.listen(1234);
	std::cout << "fd: " << sock::get_fd() << std::endl;
	return 0;
}
