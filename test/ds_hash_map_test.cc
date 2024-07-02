#include<gtest/gtest.h>
#include<cstring>
#include<ds/hash_map.hh>

struct HashMapTest: public testing::Test {
	ds::hash_map* hm;
	void SetUp(){
		hm = new ds::hash_map(4);
	}
	void TearDown(){
		delete hm;
	}
};


TEST_F(HashMapTest, ClusterSize) {
	EXPECT_EQ(hm->cluster_size(), 4);
}

TEST_F(HashMapTest, NodeSize) {
	std::string key = "key";
	std::string value = "value";
	hm->insert(key, value);
	EXPECT_EQ(hm->size(), 1);
}

TEST_F(HashMapTest, Insert) {
	std::string key1 = "key1";
	std::string value = "value";
	hm->insert(key1, value);
	std::string key2 = "key2";
	hm->insert(key2, value);
	EXPECT_EQ(hm->size(), 2);
}

TEST_F(HashMapTest, SearchFound) {
	std::string key1 = "key1";
	std::string value = "value";
	hm->insert(key1, value);
	std::string key2 = "key2";
	hm->insert(key2, value);
	EXPECT_STREQ(hm->search(key2).c_str(), value.c_str());
}

TEST_F(HashMapTest, SearchNotFound) {
	std::string key1 = "key1";
	std::string value = "value";
	hm->insert(key1, value);
	std::string key2 = "key2";
	std::string nf = "Not Found";
	EXPECT_STREQ(hm->search(key2).c_str(), nf.c_str());
}

TEST_F(HashMapTest, RemoveSuccess) {
	std::string key1 = "key1";
	std::string value = "value";
	hm->insert(key1, value);
	std::string key2 = "key2";
	hm->insert(key2, value);
	hm->remove(key1);
	EXPECT_EQ(hm->size(), 1);
}

TEST_F(HashMapTest, RemoveFailed) {
	std::string key1 = "key1";
	std::string value = "value";
	hm->insert(key1, value);
	std::string key2 = "key2";
	hm->insert(key2, value);
	std::string key3 = "key3";
	hm->remove(key3);
	EXPECT_EQ(hm->size(), 2);
}

