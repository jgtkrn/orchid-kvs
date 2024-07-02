#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <ctype.h>
#include <orc_config/dictionary.hh>

#ifndef CONFIG_GENERATOR
#define CONFIG_GENERATOR

namespace orc_config {
    /**
     * setup_config()
     * set config value depend on key, and validate value.
     */
    void setup_config(std::string& key, std::string& value, orc_config::dictionary& cfg);

    /**
     * generate()
     * generate configuration dictionary which later
     * will be consumed by orchid server.
     */
    bool generate(std::string& filename, orc_config::dictionary& cfg);

    /**
     * args_config_server()
     * process config value from CLI arguments.
     */
    void args_config_server(int argc, char* argv[], orc_config::dictionary& cfg);

    /**
     * args_config_client()
     * process config value from CLI arguments. but only for orchid-cli.
     */
    void args_config_client(int argc, char* argv[], orc_config::dictionary& cfg);
} // namespace config
#endif // CONFIG_GENERATOR
