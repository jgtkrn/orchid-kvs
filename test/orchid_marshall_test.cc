#include<gtest/gtest.h>
#include<orchid/marshall.hh>
#include<string>
#include<cstring>

TEST(MarshallTest, Marshalling) {
	std::string a = "SET NAME user";
	std::string marshall = orchid::marshall::marshall_from(a);
	std::string a_marshall = "#3\r\n$3\r\nSET\r\n$4\r\nNAME\r\n$4\r\nuser\r\n";
	EXPECT_STREQ(marshall.c_str(), a_marshall.c_str());
}

TEST(MarshallTest, Unmarshalling) {
	std::string a_marshall = "#3\r\n$3\r\nSET\r\n$4\r\nNAME\r\n$4\r\nuser\r\n";
	orchid::marshall::orchid_entry a_unmarshall = orchid::marshall::unmarshall_from(a_marshall);
	std::string val = "user";
	EXPECT_STREQ(a_unmarshall.value.c_str(), val.c_str());
}

TEST(MarshallTest, OrchidStringValidation) {
	std::string a_marshall = "#3\r\n$3\r\nSET\r\n$4\r\nNAME\r\n$4\r\nuser\r\n";
	EXPECT_TRUE(orchid::marshall::validate_format(a_marshall));
}

TEST(MarshallTest, TearString) {
	std::string a = "SET NAME user";
	std::vector<std::string> tokens = orchid::marshall::tear_string(a);
	std::string val = "user";
	EXPECT_STREQ(val.c_str(), tokens[2].c_str());
}
