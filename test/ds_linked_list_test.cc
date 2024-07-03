#include<gtest/gtest.h>
#include<cstring>
#include<ds/linked_list.hh>

struct LinkedListTest: public testing::Test {
	ds::linked_list *ll;
	void SetUp() {
		ll = new ds::linked_list();
	}
	void TearDown() {
		delete ll;
	}
};

TEST_F(LinkedListTest, Attach) {
	ds::entry_node* node = new ds::entry_node("key", "value");
	ll->attach(node);
	EXPECT_EQ(ll->_size, 1);
	delete node;
}

TEST_F(LinkedListTest, Detach) {
	ds::entry_node* node1 = new ds::entry_node("key1", "value");
	ds::entry_node* node2 = new ds::entry_node("key2", "value");
	ds::entry_node* node3 = new ds::entry_node("key3", "value");
	ll->attach(node1);
	ll->attach(node2);
	ll->attach(node3);
	std::string detach = "key1";
	ll->detach(detach);
	EXPECT_EQ(ll->_size, 2);
	delete node2;
	delete node3;
}

TEST_F(LinkedListTest, Search) {
	ds::entry_node* node = new ds::entry_node("key", "value");
	ll->attach(node);
	std::string target = "key";
	std::string value = "value";
	ds::entry_node* target_node = ll->search(target);
	EXPECT_STREQ(target_node->_value.c_str(), value.c_str());
	delete node;
}

TEST_F(LinkedListTest, Close) {
	ds::entry_node* node1 = new ds::entry_node("key1", "value");
	ds::entry_node* node2 = new ds::entry_node("key2", "value");
	ds::entry_node* node3 = new ds::entry_node("key3", "value");
	ll->attach(node1);
	ll->attach(node2);
	ll->attach(node3);
	EXPECT_EQ(ll->_size, 3);
	ll->close();
	EXPECT_EQ(ll->_size, 0);
}
