#include<orchid/socket.hh>
#include<em/em.hh>

namespace orchid {
	socket::socket(){
		SOCKET new_fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if(!ISVALIDSOCKET(new_fd)) {
			socket::set_runner(-1);
			em::err_msg("Failed to init socket fd...");
		}

		int sock_val = 1;
		SOCKET setsock = ::setsockopt(new_fd, SOL_SOCKET, SO_REUSEADDR, &sock_val, sizeof(sock_val));
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

	int socket::recv(SOCKET target_fd, char *message, size_t len) {
		int buff_len = ::recv(target_fd, message, len, 0);
    		if(buff_len > 0) message[buff_len] = 0;
    		return buff_len;
	}

	void socket::send(SOCKET target_fd, std::string message) {
		char *temp_msg = message.data();
		int buff_len = ::send(target_fd, temp_msg, message.size(), 0);
		if(buff_len == -1) em::err_msg("Failed send data...");
		if(buff_len == 0) em::err_msg("No data was sent...");
	}

	void tcp_listener::listen(size_t port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0); // define port
		int bd = ::bind(tcp_listener::get_fd(), reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
		if(ISSOCKERR(bd)) {
			tcp_listener::set_runner(-1);
			em::err_msg("Failed to bind socket fd...");
		}

		int lis = ::listen(tcp_listener::get_fd(), SOMAXCONN);
		if(ISSOCKERR(lis)) {
			tcp_listener::set_runner(-1);
			em::err_msg("Failed listen to socket...");
		}
    		int flags = fcntl(tcp_listener::get_fd(), F_GETFL, 0);
		if(-1 == flags) {
			tcp_listener::set_runner(-1);
        		em::err_msg("Failed to get flag status...");
    		}

		if(-1 == fcntl(tcp_listener::get_fd(), F_SETFL, flags | O_NONBLOCK)) {
			tcp_listener::set_runner(-1);
			em::err_msg("Failed to set flag status...");
		}
		std::stringstream stream_msg;
		stream_msg << "Server listening to port: " << port;
		std::string success_listen = stream_msg.str();
		em::norm_msg(success_listen);
	}

	SOCKET tcp_listener::accept() {
		struct sockaddr_in addr;
		socklen_t addr_len = sizeof(addr);
		SOCKET conn_fd = ::accept(tcp_listener::get_fd(), reinterpret_cast<struct sockaddr*>(&addr), &addr_len);
		if(!ISVALIDSOCKET(conn_fd)) {
			if(GETSOCKETERRNO() == EAGAIN || GETSOCKETERRNO() == EWOULDBLOCK) {
				return conn_fd;
			} else {
				return conn_fd;
			}
		}
		return conn_fd;
	}

	void tcp_streamer::connect(size_t port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0); // define port
		int conn = ::connect(tcp_streamer::get_fd(), reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
		if(ISSOCKERR(conn)) {
			tcp_streamer::set_runner(-1);
			em::err_msg("Failed connect to server...");
		} else {
			std::stringstream stream_msg;
			stream_msg << "Client connected to port: " << port;
			std::string report = stream_msg.str();
			std::cout << report << std::endl;
		}
	}

	int socket::check_closed_connection(SOCKET target_fd) {
		char message[1];
		int buff_len = ::recv(target_fd, message, 1, MSG_PEEK | MSG_DONTWAIT);
		return buff_len;
	}
}
