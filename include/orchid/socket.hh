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

#ifndef ORCHID_SOCKET
#define ORCHID_SOCKET

namespace orchid {
	class socket {
		private:
			SOCKET fd;
			short runner = 0;
		public:
			socket();
			void init();
			SOCKET get_fd();
			void set_fd(SOCKET new_fd);
			short get_runner();
			void set_runner(short val);
			int recv(SOCKET target_fd, char *message, unsigned short len);
			int send(SOCKET target_fd, std::string& message);
			void close();
	};

	class tcp_listener: public socket {
		public:
			void listen(unsigned short port);
			SOCKET accept();
	};

	class tcp_streamer: public socket {
		public:
			void connect(unsigned short port);
	};

	namespace utils {
		short set_socket_to_non_block(SOCKET target_fd); // TODO
		short check_closed_connection(SOCKET target_fd);
	} // namespace utils
} // namespace orchid
#endif // ORCHID_SOCKET
