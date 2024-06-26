#include<iostream>
#include<string>
#include<orchid/socket.hh>

int main(){
	orchid::tcp_listener sock;
	sock.init();
	sock.listen(1234);
	std::cout << "fd: " << sock.get_fd() << std::endl;

	while(1){
		if(-1 == sock.get_runner()) break;
		SOCKET conn = sock.accept();
		if(conn < 0) continue;
		while(1) {
			char message[READ_LEN];
			int recv_len = sock.recv(conn, message, READ_LEN);
			if(-1 == recv_len) continue;
			std::cout << message << std::endl;
		}
	}
	sock.close();
	return 0;
}
