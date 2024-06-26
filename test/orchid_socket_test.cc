#include<gtest/gtest.h>
#include<orchid/socket.hh>

TEST(SocketInit, Socket) {
	orchid::socket sock;
	sock.init();
	EXPECT_GT(sock.get_fd(), 2);
	sock.close();
}

TEST(SocketInit, SocketClosed) {
	orchid::socket sock;
	sock.init();
	sock.close();
	EXPECT_EQ(sock.get_fd(), -1);
}

TEST(SocketInit, TCPListener) {
	orchid::tcp_listener sock;
	sock.init();
	EXPECT_GT(sock.get_fd(), 2);
	sock.close();
}

TEST(SocketInit, TCPListenerClosed) {
	orchid::tcp_listener sock;
	sock.init();
	sock.close();
	EXPECT_EQ(sock.get_fd(), -1);
}

TEST(SocketInit, TCPStreamer) {
	orchid::tcp_streamer sock;
	sock.init();
	EXPECT_GT(sock.get_fd(), 2);
	sock.close();
}

TEST(SocketInit, TCPStreamerClosed) {
	orchid::tcp_streamer sock;
	sock.init();
	sock.close();
	EXPECT_EQ(sock.get_fd(), -1);
}
