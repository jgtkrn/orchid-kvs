#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>

typedef int SOCKET;

#define ISVALIDSOCKET(s) ((s) >= 0)
#define GETSOCKETERRNO() (errno)
#define ISSOCKERR(s) ((s) != 0)

#define READ_LEN 4096

#ifndef ORCHID_SOCKET_H
#define ORCHID_SOCKET_H

namespace orchid {
	class socket {
		private:
			SOCKET fd;
			std::string buffer;
			int runner = 0;
		public:
			socket();
			void init();
			SOCKET get_fd();
			void set_fd(SOCKET new_fd);
			int get_runner();
			void set_runner(int val);
			int recv(SOCKET target_fd, char *message, int len);
			void send(SOCKET target_fd, std::string& message);
			void close();
			int check_closed_connection(SOCKET target_fd);
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
} // namespace orchid
#endif // ORCHID_SOCKET_H
