#include<orchid/socket.hh>
#include<em/em.hh>

namespace orchid {
	socket::socket(){
		SOCKET new_fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if(!ISVALIDSOCKET(new_fd)) {
			socket::set_runner(-1);
			em::err_msg("Failed to init socket fd...");
		}

		SOCKET setsock = manage_sock_option(new_fd);
		if(ISSOCKERR(setsock)) {
			socket::set_runner(-1);
			em::err_msg("Failed to set socket options...");
		}
		socket::set_fd(new_fd);
	}

	void socket::set_fd(SOCKET new_fd) {
		fd = new_fd;
	}

	SOCKET socket::get_fd() {
		return fd;
	}

	int socket::get_runner() {
		return runner;
	}

	void socket::set_runner(int val) {
		runner = val;
	}

	void socket::close() {
		::close(get_fd());
	}

	std::string socket::recv(SOCKET target_fd) {
		char temp_buffer[4096]; // TODO: config default buffer
		int bytes_len;
		while (1) {
			bytes_len = ::recv(target_fd, temp_buffer, sizeof(temp_buffer), 0);
			if (bytes_len < 0) {
				em::err_msg("Failed receive data...");
				break;
			} else if (bytes_len == 0) {
				em::err_msg("No data received...");
				break;
			}
			buffer.append(temp_buffer, bytes_len);
		}
		return buffer;
	}

	void socket::send(SOCKET target_fd, std::string message) {
		char *temp_msg = message;
		int buff_len = ::send(target_fd, temp_msg, message.size(), 0);
		if(buff_len == -1) em::err_msg("Failed send data...");
		if(buff_len == 0) em::err_msg("No data was sent...");
	}

	void socket::sendata(){
		std::cout << "Hello Orchid \n";
	}

	void socket::set_addr(size_t port) {
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0); // define port
	}

	struct sockaddr_in socket::get_addr() {
		return addr;
	}

	void tcp_listener::listen(size_t port) {
		tcp_listener::set_addr(port);
		int bd = ::bind(tcp_listener::get_fd(), (const struct sockaddr*)addr, sizeof(addr));
		if(ISSOCKERR(bd)) {
			tcp_listener::set_runner(-1);    
			em::err_msg("Failed to bind socket fd...");
		}

		int lis = ::listen(tcp_listener::get_fd(), SOMAXCONN);
		if(ISSOCKERR(lis)) {
			tcp_listener::set_runner(-1);
			em::err_msg("Failed listen to socket...");
		}

	}

	SOCKET tcp_listener::accept() {
		socklen_t sock_len = sizeof(addr);
		SOCKET conn_fd = ::accept(tcp_listener::get_fd(), (struct sockaddr*)&addr, &sock_len);
		if(!ISVALIDSOCKET(conn_fd)) {
			if(GETSOCKETERRNO() == EAGAIN || GETSOCKETERRNO() == EWOULDBLOCK) {
				tcp_listener::set_runner(-1);
				em::err_msg("Failed connection blocked...");
				return conn_fd;
			} else {
				tcp_listener::set_runner(-1);
				em::err_msg("Failed accepting connection...");
				return conn_fd;
			}
		}
		return conn_fd;
	}

	void tcp_streamer::connect(size_t port) {
		tcp_streamer::set_addr(port);
		int conn = ::connect(tcp_streamer::get_fd(), (const struct sockaddr*)&addr, sizeof(addr));
		if(ISSOCKERR(conn)) {
			tcp_streamer::set_runner(-1);
			em::err_msg("Failed connect to server ...");
		}
	}

	int check_closed_connection(SOCKET target_fd) {
		char message[1];
		int buff_len = ::recv(target_fd, message, 1, MSG_PEEK | MSG_DONTWAIT);
		return buff_len;
	}

	SOCKET manage_sock_option(SOCKET new_fd) {
		int sock_val = 1;
		SOCKET setsock = ::setsockopt(new_fd, SOL_SOCKET, SO_REUSEADDR, &sock_val, sizeof(sock_val));
		return setsock;
	}

}
