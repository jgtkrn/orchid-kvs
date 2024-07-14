#include<gtest/gtest.h>
#include<cron/cron.hh>

TEST(SetTime, SuccessSetTime) {
	EXPECT_EQ(cron::time_mapper("2d3h4m1s5ms300us"), 183841005300);
}

TEST(SetTime, FailedSetTime) {
	EXPECT_EQ(cron::time_mapper("2abc"), -1);
}