#include<orchid/socket.hh>

namespace orchid {
	socket::socket(): _fd(-1), _runner(0) {}
	void socket::init(){
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
		_fd = new_fd;
	}

	SOCKET socket::get_fd() {
		return _fd;
	}

	short socket::get_runner() {
		return _runner;
	}

	void socket::set_runner(short val) {
		_runner = val;
	}

	void socket::close() {
		if(_fd > 0) ::close(_fd);
		_fd = -1;
	}
	/**
		NOTE: under efficiency
	*/
	int socket::recv(SOCKET target_fd, std::string& message) {
		char temp_buffer[READ_LEN];
		int buff_len = 0;
		//std::cout << "" << std::endl;
		//while(true) {
			int recv_len = ::recv(target_fd, temp_buffer, READ_LEN, 0);
			//if(recv_len == 0) continue;
			//if(recv_len == -1) break;
			if(recv_len > 0) {
			buff_len += recv_len;
			temp_buffer[recv_len] = 0;
			message.append(temp_buffer, recv_len);
			}
		//}
    		return buff_len;
	}

	int socket::send(SOCKET target_fd, std::string& message) {
		char *temp_msg = message.data();
		int buff_len = ::send(target_fd, temp_msg, message.size(), 0);
		if(buff_len == -1) std::cout << "Failed send data..." << std::endl;
		if(buff_len == 0) std::cout << "No data was sent..." << std::endl;
		return buff_len;
	}

	void tcp_listener::listen(unsigned short port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0);
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

		std::stringstream stream_msg;
		stream_msg << "Server listening to port: " << port;
		std::cout << stream_msg.str() << std::endl;
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

	void tcp_streamer::connect(unsigned short port) {
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
			std::cout << "conn: " << conn << std::endl;
		}
	}
}
