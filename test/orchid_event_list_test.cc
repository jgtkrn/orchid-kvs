#include<gtest/gtest.h>
#include<orchid/event_list.hh>

struct EventListTest: public testing::Test {
        orchid::event_list *evl;
        void SetUp() { evl = new orchid::event_list(); }
        void TearDown() {
                delete evl;
        }
};

TEST_F(EventListTest, EvlAttach){
	evl->attach(3);
	EXPECT_EQ(evl->_size, 1);
}
TEST_F(EventListTest, EvlDetach){
	evl->attach(1);
	evl->attach(1);
	EXPECT_EQ(evl->_size, 2);
}
