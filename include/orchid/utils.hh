#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>

/**
 * redefine int as SOCKET for easier reading, since file descriptor is an integer.
 */
typedef int SOCKET;

#ifndef ORCHID_UTILS
#define ORCHID_UTILS

/**
 * utils were separated from socket class
 * because it will be more functional if can work
 * generaly with any kind of socket file descriptor
 * no matter if it is a listening or connecting fd.
 */
namespace orchid {
	namespace utils {
		/**
		 * set_socket_to_non_block()
		 * set socket file descriptor flags to non blocking mode,
		 * so latter can work with the event dispatcher.
		 */
		short set_socket_to_non_block(SOCKET target_fd);

		/**
		 * check_closed_connection()
		 * sometimes event flags does not work well,
		 * this function exists to make sure whether
		 * the client already closed.
		 */
		short check_closed_connection(SOCKET target_fd);
	} // namespace utils
} // namespace orchid
#endif // ORCHID_UTILS
