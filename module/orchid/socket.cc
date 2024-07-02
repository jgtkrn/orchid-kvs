#include<orchid/socket.hh>

namespace orchid {
	socket::socket(): _fd(-1), _runner(0), _socket_read_len(SOCKET_READ_LEN) {}
	socket::socket(orc_config::dictionary& cfg): _fd(-1), _runner(0), _socket_read_len(cfg.socket_read_len) {}
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

	int socket::recv(SOCKET target_fd, std::string& message) {
		char temp_buffer[_socket_read_len];
		int buff_len = 0;
		while(true) {
			int recv_len = ::recv(target_fd, temp_buffer, _socket_read_len, 0);
			if(recv_len == 0) {
				break;
			}
			if(recv_len < 0) {
				break;
			}
			if(recv_len > 0) {
				buff_len += recv_len;
				message.append(temp_buffer, recv_len);
				if(recv_len < _socket_read_len) break;
			}
		}
    		return buff_len;
	}

	int socket::send(SOCKET target_fd, std::string& message) {
		char *temp_msg = message.data();
		int buff_len = ::send(target_fd, temp_msg, message.size(), 0);
		if(buff_len == -1) std::cout << "Failed send data..." << std::endl;
		if(buff_len == 0) std::cout << "No data was sent..." << std::endl;
		return buff_len;
	}

	tcp_listener::tcp_listener(): socket(), _server_host(DEFAULT_HOST), _server_port(DEFAULT_PORT) {}

	tcp_listener::tcp_listener(orc_config::dictionary& cfg): socket(cfg), _server_host(cfg.server_host), _server_port(cfg.server_port) {}

	void tcp_listener::listen() {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(_server_port);
		inet_pton(AF_INET, _server_host.c_str(), &(addr.sin_addr));
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
		stream_msg << "Server listening to port: " << _server_port;
		std::cout << stream_msg.str() << std::endl;
	}

	tcp_streamer::tcp_streamer(): socket(), _client_host(DEFAULT_HOST), _client_port(DEFAULT_PORT) {}

	tcp_streamer::tcp_streamer(orc_config::dictionary& cfg): socket(cfg), _client_host(cfg.server_host), _client_port(cfg.server_port) {}

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

	void tcp_streamer::connect() {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(_client_port);
		inet_pton(AF_INET, _client_host.c_str(), &(addr.sin_addr));
		int conn = ::connect(get_fd(), reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
		if(ISSOCKERR(conn)) {
			set_runner(-1);
			std::cout << "Failed connect to server..." << std::endl;
		} else {
			std::stringstream stream_msg;
			stream_msg << "Client connected to port: " << _client_port;
			std::cout << stream_msg.str() << std::endl;
		}
	}
}
