#include<orchid/utils.hh>
namespace orchid {
	namespace utils {
		short set_socket_to_non_block(SOCKET target_fd) {
			int flags = ::fcntl(target_fd, F_GETFL, 0);
			if(-1 == flags) {
				return -1;
        		std::cout << "Failed to get flag status..." << std::endl;
    		}

			if(-1 == ::fcntl(target_fd, F_SETFL, flags | O_NONBLOCK)) {
				return -1;
				std::cout << "Failed to set flag status..." << std::endl;
			}
			return 0;
		}
		short check_closed_connection(SOCKET target_fd) {
			char message[1];
			short buff_len = ::recv(target_fd, message, 1, MSG_PEEK | MSG_DONTWAIT);
			return buff_len;
		}
	} // namespace utils
} // namespace orchid