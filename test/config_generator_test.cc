#include<gtest/gtest.h>
#include<cstring>
#include<config/generator.hh>

struct GeneratorTest: public testing::Test {
	config::dictionary cfg;
    std::string filename = "test/test.conf";
	void SetUp(){}
	void TearDown(){}
};

TEST_F(GeneratorTest, InitConfig) {
    config::generate(filename, cfg);
    std::string host = "127.0.0.1";
    EXPECT_STREQ(cfg.server_host.c_str(), host.c_str());
    EXPECT_STREQ(cfg.client_host.c_str(), host.c_str());
    EXPECT_EQ(cfg.server_port, 1234);
    EXPECT_EQ(cfg.client_port, 1234);
    EXPECT_EQ(cfg.socket_read_len, 16);
    EXPECT_EQ(cfg.hm_cluster_size, 8);
}

TEST_F(GeneratorTest, SetupConfig) {
    std::string key = "server_port";
    std::string value = "3456";
    config::setup_config(key, value, cfg);
    EXPECT_EQ(cfg.server_port, 3456);
}

TEST_F(GeneratorTest, ManageServerArgs) {
    int argc = 1;
    char* argv[] = {"-p", "3456"};
    config::args_config_server(argc,argv,cfg);
    EXPECT_EQ(cfg.server_port, 3456);
}

TEST_F(GeneratorTest, ManageClientArgs) {
    int argc = 1;
    char* argv[] = {"-p", "3456"};
    config::args_config_client(argc,argv,cfg);
    EXPECT_EQ(cfg.client_port, 3456);
}