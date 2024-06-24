#pragma once
#ifndef ORCHID_SOCKET
#define ORCHID_SOCKET
#endif

#define SOCKET int

#include<iostream>
#include<string>

namespace orchid {
	class socket {
		private:
			SOCKET fd;
			int port;
			std::string address;
		public:
			socket();
			std::string recv(int fd);
			void send(int fd, std::string);
			void sendata();
			void close();
	};
	class tcp_listener: public socket {
		void listen();
		void accept();
	};
	class tcp_streamer: public socket {
		void connect();
	};
} // namespace orchid
