#include<orchid/socket.hh>
#include<gtest/gtest.h>

TEST(SocketInitiation, Socket) {
	orchid::socket sock;
	EXPECT_GT(sock.get_fd(), 2);
}

TEST(SocketInitiation, TCPListener) {
	orchid::tcp_listener sock;
	EXPECT_GT(sock.get_fd(), 2);
}

TEST(SocketInitiation, TCPStreamer) {
	orchid::tcp_streamer sock;
	EXPECT_GT(sock.get_fd(), 2);
}

int main() {
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

