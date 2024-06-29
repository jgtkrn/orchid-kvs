#include<gtest/gtest.h>
#include<orchid/socket.hh>
#include<orchid/utils.hh>

TEST(SetNB, SuccessSetNB) {
	orchid::socket sock;
	sock.init();
	EXPECT_EQ(orchid::utils::set_socket_to_non_block(sock.get_fd()), 0);
}

TEST(SetNB, FailedSetNB) {
	EXPECT_EQ(orchid::utils::set_socket_to_non_block(-1), -1);
}

TEST(ClosedFD, NoValFD) {
	EXPECT_EQ(orchid::utils::check_closed_connection(-1), -1);
}
