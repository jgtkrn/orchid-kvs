#ifndef ORCHID_SOCKET
#define ORCHID_SOCKET
#endif

#include<iostream>
#include<string>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>

#define SOCKET int

#define ISVALIDSOCKET(s) ((s) >= 0)
#define GETSOCKETERRNO() (errno)
#define ISSOCKERR(s) ((s) != 0)

namespace orchid {
	class socket {
		private:
			SOCKET fd;
			std::string buffer;
			int runner = 0;
		public:
			socket();
			SOCKET get_fd();
			void set_fd(SOCKET fd);
			std::string recv(SOCKET fd);
			void send(SOCKET fd, std::string);
			void close();
			int get_runner();
			void set_runner();
			void sendata();
	};

	class tcp_listener: public socket {
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
