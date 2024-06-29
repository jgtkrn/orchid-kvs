#include<iostream>
#include<string>
#include<orchid/socket.hh>
#include<orchid/utils.hh>
#include<orchid/event_dispatcher.hh>

int main(){
	orchid::tcp_listener sock;
	sock.init();
	sock.listen(1234);
	orchid::utils::set_socket_to_non_block(sock.get_fd());
	orchid::event_dispatcher evd;
	evd.init();
	evd.attach_event(sock.get_fd());
	while(true){
		if(-1 == sock.get_runner()) break;
		if(-1 == evd.watch_event()) break;
		for(int i = 0; i < evd.get_nfds(); ++i) {
			if(evd.get_index_efd(i) == sock.get_fd()) {
				SOCKET conn = sock.accept();
				if(conn < 0) continue;
				orchid::utils::set_socket_to_non_block(conn);
				evd.attach_event(conn);
			} else {
				char message[READ_LEN];
				int recv_len = sock.recv(evd.get_index_efd(i), message, READ_LEN);
				if(-1 == recv_len) continue;
				std::cout << message << std::endl;
			}
		}
	}
	sock.close();
	evd.close();
	return 0;
}
