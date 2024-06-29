#include<gtest/gtest.h>
#include<orchid/socket.hh>
#include<orchid/event_dispatcher.hh>
#include<orchid/utils.hh>

struct EventDispatcherTest: public testing::Test {
	orchid::event_dispatcher *evd;
	void SetUp() { evd = new orchid::event_dispatcher(); }
	void TearDown() {
		evd->close();
		delete evd;
	}
};

TEST_F(EventDispatcherTest, EvdInit) {
	evd->init();
	EXPECT_TRUE(evd->get_fd() > 0);
}

TEST_F(EventDispatcherTest, EvdClose) {
	evd->init();
	evd->close();
	EXPECT_EQ(evd->get_fd(), -1);
}

TEST_F(EventDispatcherTest, EvdAttachEventSuccess) {
	orchid::socket sock;
	sock.init();
	evd->init();
	EXPECT_TRUE(evd->attach_event(sock.get_fd()));
}

TEST_F(EventDispatcherTest, EvdAttachEventFailed) {
	evd->init();
	EXPECT_FALSE(evd->attach_event(-1));
}

TEST_F(EventDispatcherTest, EvdDetachEventSuccess) {
	orchid::socket sock;
	sock.init();
	evd->init();
	evd->attach_event(sock.get_fd());
	EXPECT_TRUE(evd->detach_event(sock.get_fd()));
}

TEST_F(EventDispatcherTest, EvdDetachEventFailed) {
	evd->init();
	EXPECT_FALSE(evd->detach_event(-1));
}

TEST_F(EventDispatcherTest, EvdWatchEvent) {
	orchid::socket sock;
	sock.init();
	evd->init();
	evd->attach_event(sock.get_fd());
	EXPECT_EQ(evd->watch_event(), 1);
}

TEST_F(EventDispatcherTest, EvdSetFd) {
        evd->set_fd(5);
        EXPECT_EQ(evd->get_fd(), 5);
}

TEST_F(EventDispatcherTest, EvdGetFd) {
        EXPECT_EQ(evd->get_fd(), -1);
}

TEST_F(EventDispatcherTest, EvdSetRunner) {
        evd->set_runner(5);
        EXPECT_EQ(evd->get_runner(), 5);
}

TEST_F(EventDispatcherTest, EvdGetRunner) {
        EXPECT_EQ(evd->get_runner(), 0);
}

TEST_F(EventDispatcherTest, EvdGetNFDS) {
	orchid::socket sock;
	sock.init();
	evd->init();
	evd->attach_event(sock.get_fd());
	evd->watch_event();
	EXPECT_EQ(evd->get_nfds(), 1);
}

TEST_F(EventDispatcherTest, EvdGetIndexFD) {
	orchid::socket sock;
	sock.init();
	evd->init();
	evd->attach_event(sock.get_fd());
	evd->watch_event();
	EXPECT_TRUE(evd->get_index_efd(0) > 3);
}

