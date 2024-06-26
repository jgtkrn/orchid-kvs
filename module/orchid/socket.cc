#include<orchid/socket.hh>

namespace orchid {
	socket::socket(): fd(-1), runner(0) {
		SOCKET new_fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if(!ISVALIDSOCKET(new_fd)) {
			set_runner(-1);
			std::cout << "Failed to init socket fd..." << std::endl;
		}

		int sock_val = 1;
		SOCKET setsock = ::setsockopt(new_fd, SOL_SOCKET, SO_REUSEADDR, &sock_val, sizeof(sock_val));
		if(ISSOCKERR(setsock)) {
			set_runner(-1);
			std::cout << "Failed to set socket options..." << std::endl;
		}
		set_fd(new_fd);
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
		if(fd > 0) {
			::close(fd);
			fd = -1;
		}
	}

	int socket::recv(SOCKET target_fd, char *message, size_t len) {
		int buff_len = ::recv(target_fd, message, len, 0);
    		if(buff_len > 0) message[buff_len] = 0;
    		return buff_len;
	}

	void socket::send(SOCKET target_fd, std::string& message) {
		char *temp_msg = message.data();
		int buff_len = ::send(target_fd, temp_msg, message.size(), 0);
		if(buff_len == -1) std::cout << "Failed send data..." << std::endl;
		if(buff_len == 0) std::cout << "No data was sent..." << std::endl;
	}

	void tcp_listener::listen(size_t port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0); // define port
		int bd = ::bind(get_fd(), reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
		if(ISSOCKERR(bd)) {
			set_runner(-1);
			std::cout << "Failed to bind socket fd..." << std::endl;
		}

		int lis = ::listen(get_fd(), SOMAXCONN);
		if(ISSOCKERR(lis)) {
			set_runner(-1);
			std::cout << "Failed listen to socket..." << std::endl;
		}

    	int flags = ::fcntl(get_fd(), F_GETFL, 0);
		if(-1 == flags) {
			set_runner(-1);
        		std::cout << "Failed to get flag status..." << std::endl;
    		}

		if(-1 == ::fcntl(get_fd(), F_SETFL, flags | O_NONBLOCK)) {
			set_runner(-1);
			std::cout << "Failed to set flag status..." << std::endl;
		}
		std::stringstream stream_msg;
		stream_msg << "Server listening to port: " << port;
		std::string success_listen = stream_msg.str();
		std::cout << success_listen << std::endl;
	}

	SOCKET tcp_listener::accept() {
		struct sockaddr_in addr;
		socklen_t addr_len = sizeof(addr);
		SOCKET conn_fd = ::accept(get_fd(), reinterpret_cast<struct sockaddr*>(&addr), &addr_len);
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
		int conn = ::connect(get_fd(), reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
		if(ISSOCKERR(conn)) {
			set_runner(-1);
			std::cout << "Failed connect to server..." << std::endl;
		} else {
			std::stringstream stream_msg;
			stream_msg << "Client connected to port: " << port;
			std::cout << stream_msg.str() << std::endl;
		}
	}

	int socket::check_closed_connection(SOCKET target_fd) {
		char message[1];
		int buff_len = ::recv(target_fd, message, 1, MSG_PEEK | MSG_DONTWAIT);
		return buff_len;
	}
}
