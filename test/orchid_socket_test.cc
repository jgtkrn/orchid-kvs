#include<gtest/gtest.h>
#include<orchid/socket.hh>

struct SocketTest: public testing::Test {
	orchid::socket *sock;
	void SetUp() { sock = new orchid::socket(); }
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
	EXPECT_GT(sock->get_fd(), 5);
}

TEST_F(SocketTest, SocketGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(SocketTest, SocketSetRunner) {
	sock->set_runner(5);
	EXPECT_GT(sock->get_runner(), 5);
}

TEST_F(SocketTest, SocketGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(SocketTest, SocketRecv) {
	char message[1024];
	int len = sock->recv(5, message, 1024);
	EXPECT_TRUE(len >= -1);
}

TEST_F(SocketTest, SocketSend) {
	EXPECT_TRUE(sock->send(5, "test") >= -1);
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
	EXPECT_GT(sock->get_fd(), 5);
}

TEST_F(TCPListenerTest, TCPListenerGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPListenerTest, TCPListenerSetRunner) {
	sock->set_runner(5);
	EXPECT_GT(sock->get_runner(), 5);
}

TEST_F(TCPListenerTest, TCPListenerGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(TCPListenerTest, TCPListenerRecv) {
	char message[1024];
	int len = sock->recv(5, message, 1024);
	EXPECT_TRUE(len >= -1);
}

TEST_F(TCPListenerTest, TCPListenerSend) {
	EXPECT_TRUE(sock->send(5, "test") >= -1);
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
	EXPECT_GT(sock->get_fd(), 5);
}

TEST_F(TCPStreamerTest, TCPStreamerGetFd) {
	EXPECT_EQ(sock->get_fd(), -1);
}

TEST_F(TCPStreamerTest, TCPStreamerSetRunner) {
	sock->set_runner(5);
	EXPECT_GT(sock->get_runner(), 5);
}

TEST_F(TCPStreamerTest, TCPStreamerGetRunner) {
	EXPECT_EQ(sock->get_runner(), 0);
}

TEST_F(TCPStreamerTest, TCPStreamerRecv) {
	char message[1024];
	int len = sock->recv(5, message, 1024);
	EXPECT_TRUE(len >= -1);
}

TEST_F(TCPStreamerTest, TCPStreamerSend) {
	EXPECT_TRUE(sock->send(5, "test") >= -1);
}