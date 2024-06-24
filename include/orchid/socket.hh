#ifndef ORCHID_SOCKET
#define ORCHID_SOCKET
#endif

#define SOCKET int

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define GETSOCKETERRNO() (errno)
#define ISSOCKERR(s) ((s) != 0)

#include<iostream>
#include<string>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>

namespace orchid {
	class socket {
		private:
			SOCKET fd;
			int runner = 0;
			std::string buffer;
		public:
			socket();
			SOCKET get_fd();
			std::string recv(SOCKET fd);
			void send(SOCKET fd, std::string);
			void close();
			int check_runner();
			void sendata();
	};

	class tcp_listener: public socket {
		private:
			struct sockaddr_in addr;
		public:
			void listen(size_t port);
			SOCKET accept();
	};

	class tcp_streamer: public socket {
		public:
			void connect(size_t port);
	};

	SOCKET manage_sock_option(SOCKET fd);
	int check_closed_connection(SOCKET fd);
} // namespace orchid
