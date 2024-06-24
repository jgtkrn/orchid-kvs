#include<orchid/socket.hh>
#include<em/em.h>

namespace orchid {
	socket::socket(){
		    fd = socket(AF_INET, SOCK_STREAM, 0);
			if(!ISVALIDSOCKET(fd)) {
				runner = -1;
				em::err_msg("Failed to init socket fd...");
			}

			SOCKET setsock = manage_sock_option(fd);
			if(ISSOCKERR(setsock)) {
				runner = -1;
				em::err_msg("Failed to set socket options...");
			}
	}

	SOCKET socket::get_fd() {
		return fd;
	}

	int socket::check_runner() {
		return runner;
	}

	void socket::close() {
		CLOSESOCKET(fd);
	}

	std::string recv(SOCKET fd) {
		char temp_buffer[4096]; // TODO: config default buffer
		int bytes_len;
		while (true) {
			bytes_len = recv(sock, temp_buffer, sizeof(temp_buffer), 0);
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

	void send(SOCKET fd, std::string message) {
		char temp_msg[message.size()] = message;
		int buff_len = send(fd, msg, message.size(), 0);
		if(buff_len == -1) em::err_msg("Failed send data...");
		if(buff_len == 0) em::err_msg("No data was sent...");
	}

	void socket::sendata(){
		std::cout << "Hello Orchid \n";
	}

	void tcp_listener::listen(size_t port) {
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0); // define port
		int bd = bind(fd, (const struct sockaddr*)&addr, sizeof(addr));
		if(ISSOCKERR(bd)) {
			runner = -1;    
			em::err_msg("Failed to bind socket fd...");
		}

		int lis = listen(fd, SOMAXCONN);
		if(ISSOCKERR(lis)) {
			runner = -1;
			em::err_msg("Failed listen to socket...");
		}
		
	}

	SOCKET tcp_listener::accept() {
		socklen_t sock_len = sizeof(addr);
		SOCKET conn_fd = accept(fd, (struct sockaddr*)&addr, &sock_len);
		if(!ISVALIDSOCKET(conn_fd)) {
			if(GETSOCKETERRNO() == EAGAIN || GETSOCKETERRNO() == EWOULDBLOCK) {
				runner = -1;
				em::err_msg("Failed connection blocked...");
				return conn_fd;
			} else {
				runner = -1;
				em::err_msg("Failed accepting connection...");
				return conn_fd;
			}        
		}    
		return conn_fd;
	}

	void tcp_streamer::connect(size_t port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ntohs(port);
		addr.sin_addr.s_addr = ntohl(0);
		int conn = connect(fd, (const struct sockaddr*)&addr, sizeof(addr));
		if(ISSOCKERR(conn)) {
			runner = -1;
			em::err_msg("Failed connect to server ...");
		}
	}

	int check_closed_connection(SOCKET fd) {
		char message[1];
		int buff_len = recv(fd, message, 1, MSG_PEEK | MSG_DONTWAIT);
		return buff_len;
	}

	SOCKET manage_sock_option(SOCKET fd) {
		int sock_val = 1;
		SOCKET setsock = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &sock_val, sizeof(sock_val));
		return setsock;
	}

}
