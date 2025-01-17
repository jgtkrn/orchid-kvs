#include<gtest/gtest.h>
#include<orchid/socket.hh>
#include<orchid/utils.hh>

struct SocketTest: public testing::Test {
	orchid::socket *sock;
	void SetUp() {
		sock = new orchid::socket();
	}
	void TearDown() {
		sock->close();
		delete sock;
	}
};

struct TCPListenerTest: public testing::Test {
	orchid::tcp_listener *sock;
	void SetUp() { sock = new orchid::tcp_listener(); }
	void TearDown() {
		sock->close();
		delete sock;
	}
};

struct TCPStreamerTest: public testing::Test {
	orchid::tcp_streamer *sock;
	void SetUp() { sock = new orchid::tcp_streamer(); }
	void TearDown() {
		sock->close();
		delete sock;
	}
};

TEST_F(SocketTest, SocketInit) {
	sock->init();
	EXPECT_GT(sock->get_fd(), 2);
}

TEST_F(SocketTest, SocketClose) {
	sock->init();
	sock->close();
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(SocketTest, SocketSetFd) {
	sock->set_fd(5);
	EXPECT_EQ(sock->get_fd(), 5);
}

TEST_F(SocketTest, SocketGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(SocketTest, SocketSetRunner) {
	sock->set_runner(5);
	EXPECT_EQ(sock->get_runner(), 5);
}

TEST_F(SocketTest, SocketGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(SocketTest, SocketRecv) {
	std::string message;
	int len = sock->recv(5, message);
	EXPECT_TRUE(len >= -1);
}

TEST_F(SocketTest, SocketSend) {
	std::string msg = "test";
	EXPECT_TRUE(sock->send(5, msg) >= -1);
}

TEST_F(TCPListenerTest, TCPListenerInit) {
	sock->init();
	EXPECT_GT(sock->get_fd(), 2);
}

TEST_F(TCPListenerTest, TCPListenerClose) {
	sock->init();
	sock->close();
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPListenerTest, TCPListenerSetFd) {
	sock->set_fd(5);
	EXPECT_EQ(sock->get_fd(), 5);
}

TEST_F(TCPListenerTest, TCPListenerGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPListenerTest, TCPListenerSetRunner) {
	sock->set_runner(5);
	EXPECT_EQ(sock->get_runner(), 5);
}

TEST_F(TCPListenerTest, TCPListenerGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(TCPListenerTest, TCPListenerRecv) {
	std::string message;
	int len = sock->recv(5, message);
	EXPECT_TRUE(len >= -1);
}

TEST_F(TCPListenerTest, TCPListenerSend) {
	std::string msg = "test";
	EXPECT_TRUE(sock->send(5, msg) >= -1);
}

TEST_F(TCPListenerTest, TCPListenerListenSuccess) {
	sock->init();
	sock->listen();
	EXPECT_TRUE(sock->get_runner() == 0);
}

TEST_F(TCPListenerTest, TCPListenerListenFailed) {
	sock->listen();
	EXPECT_TRUE(sock->get_runner() == -1);
}

TEST_F(TCPListenerTest, TCPListenerAccept) {
	sock->init();
	sock->listen();
	orchid::utils::set_socket_to_non_block(sock->get_fd());
	EXPECT_TRUE(sock->accept() >= -1);
}

TEST_F(TCPStreamerTest, TCPStreamerInit) {
	sock->init();
	EXPECT_GT(sock->get_fd(), 2);
}

TEST_F(TCPStreamerTest, TCPStreamerClose) {
	sock->init();
	sock->close();
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPStreamerTest, TCPStreamerSetFd) {
	sock->set_fd(5);
	EXPECT_EQ(sock->get_fd(), 5);
}

TEST_F(TCPStreamerTest, TCPStreamerGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPStreamerTest, TCPStreamerSetRunner) {
	sock->set_runner(5);
	EXPECT_EQ(sock->get_runner(), 5);
}

TEST_F(TCPStreamerTest, TCPStreamerGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(TCPStreamerTest, TCPStreamerRecv) {
	std::string message;
	int len = sock->recv(5, message);
	EXPECT_TRUE(len >= -1);
}

TEST_F(TCPStreamerTest, TCPStreamerSend) {
	std::string msg = "test";
	EXPECT_TRUE(sock->send(5, msg) >= -1);
}

TEST_F(TCPStreamerTest, TCPStreamerConnect) {
	sock->init();
	sock->connect();
	EXPECT_TRUE(sock->get_runner() >= -1);
}
