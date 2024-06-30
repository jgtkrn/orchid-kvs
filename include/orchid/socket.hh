#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

/**
 * redefine int as SOCKET for easier reading, since file descriptor is an integer.
 */
typedef int SOCKET;

/**
 * check if the socket has valid file descriptor which is above -1.
 */
#define ISVALIDSOCKET(s) ((s) >= 0)

/**
 * check if there is error returned.
 */
#define GETSOCKETERRNO() (errno)

/**
 * checking if the modified socket error.
 */
#define ISSOCKERR(s) ((s) != 0)

/**
 * read limit of char length received or sent.
 * this is initial limit, this will be extended
 * depend on string variable which storing this value.
 */
#define READ_LEN 32

#ifndef ORCHID_SOCKET
#define ORCHID_SOCKET

/**
 * socket class
 * is socket operation encapsulation to manage any common 
 * socket operation like listen, accept, connect,
 * send message, and receive message. 
 */

namespace orchid {
	class socket {
		private:
			/** 
			 * _fd is a variable to store socket class file descriptor. 
			 * returns -1 if socket failed to initialize and greater than
			 * 0 (commonly above 2 outside std fd).
			 */
			SOCKET _fd;

			/**
			 * _runner is an indicator to check whether this socket
			 * need to be closed. returns -1 if this socket gain issue,
			 * and 0 if no issue that require this socket closed.
			 */
			short _runner;
		public:

			socket();
			/**
			 * init()
			 * socket function to initialize socket class
			 * contains file descriptor '_fd' generation
			 * through socket initialization.
			 */
			void init();

			/**
			 * get_fd()
			 * returns initialized socket file descriptor.
			 */
			SOCKET get_fd();

			/**
			 * set_fd()
			 * file descriptor setter for current socket.
			 */
			void set_fd(SOCKET new_fd);

			/**
			 * get_runner()
			 * getter for _runner value.
			 */
			short get_runner();

			/**
			 * set_runner()
			 * setter for _runner value.
			 */
			void set_runner(short val);

			/**
			 * recv()
			 * returns length of char received dynamically from listened connection.
			 * require string refference as variable to store the values returned.
			 */
			int recv(SOCKET target_fd, std::string& message);

			/**
			 * send()
			 * returns length of char sent dynamically to target connection.
			 * require string refference which it's value will be sent.
			 */
			int send(SOCKET target_fd, std::string& message);

			/**
			 * close()
			 * release file descriptor which assigned to current socket
			 */
			void close();
	};

	class tcp_listener: public socket {
		public:
			/**
			 * listen()
			 * function to sign the port assigned for listening connection.
			 */
			void listen(unsigned short port);
			/**
			 * accept()
			 * accepting external connection, and returns assigned file descriptor.
			 */
			SOCKET accept();
	};

	class tcp_streamer: public socket {
		public:
			/**
			 * connect()
			 * takes port value to connect to target orchid server.
			 */
			void connect(unsigned short port);
	};
} // namespace orchid
#endif // ORCHID_SOCKET
