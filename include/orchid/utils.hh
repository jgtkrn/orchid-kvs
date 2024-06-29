#include<iostream>
#include<sys/socket.h>
#include<fcntl.h>
typedef int SOCKET;

#ifndef ORCHID_UTILS
#define ORCHID_UTILS
namespace orchid {
	namespace utils {
		short set_socket_to_non_block(SOCKET target_fd);
		short check_closed_connection(SOCKET target_fd);
	} // namespace utils
} // namespace orchid
#endif // ORCHID_UTILS
