#include<config/dictionary.hh>
#include<config/generator.hh>
//::isdigit(orchid_string[1])
namespace config {
    void setup_config(std::string& key, std::string& value, config::dictionary& cfg) {
        /**
        * SOCKET CONFIG 
        */
        if (key == "server_port") {
            if(::isdigit(value) && (value - '0' >= 0)) cfg.server_port = std::stoi(value);
        }
        if (key == "client_host") cfg.client_host = value;
        if (key == "client_port") {
            if(::isdigit(value) && (value - '0' >= 0)) cfg.client_port = std::stoi(value);
        }
        if (key == "socket_read_len") {
            if(::isdigit(value) && (value - '0' >= 0)) cfg.socket_read_len = std::stoi(value);
        }
        
        /**
        * HASH MAP CONFIG 
        */
        if (key == "cluster_size") {
            if(::isdigit(value) && (value - '0' >= 0)) cfg.hm_cluster_size = std::stoi(value);
        }
    }


    bool generate(const std::string& filename, config::dictionary& cfg) {
        std::string current_file_path = __FILE__;
        std::filesystem::path file_path = current_file_path.parent_path().parent_path() / filename;
        if(!std::filesystem::exists(file_path)) {
            std::out << "Configuration file does not exists in: " << file_path.string() << std::endl;
            return false;
        }
        std::ifstream file(file_path.string());
        if (!file.is_open()) {
            std::out << "Failed to open file: " << file_path.string() << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
                return !std::isspace(ch);
            }));

            if (line.empty() || line[0] == '#') {
                continue;
            }

            std::istringstream stream(line);
            std::string key;
            if (std::getline(stream, key, '=')) {
                std::string value;
                if (std::getline(stream, value)) {
                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);
                    setup_config(key, value, cfg);
                }
            }
        }

        file.close();
        return true;
    }

    void args_config_server(int argc, char* argv[], config& cfg) {
        std::string arg, key, value;
        for(short i = 0; i < argc; i+=2) {
            arg = argv[i];
            if(argv[i][0] == '-' && argv[i][1] == '-') {
                key = arg.substr(2);
                value = argv[i+1];
            } else if(argv[i][0] == '-' && !argv[i][1] == '-') {
                key = arg.substr(1);
                value = argv[i+1];
            }
            if(key == 'p' || key == 'port') {
                if(::isdigit(value) && (value - '0' >= 0)) cfg.server_port = std::stoi(value);
            }
            if(key == 'rl' || key == 'read-len') {
                if(::isdigit(value) && (value - '0' >= 0)) cfg.socket_read_len = std::stoi(value);
            }
            if(key == 'cs' || key == 'cluster-size') {
                if(::isdigit(value) && (value - '0' >= 0)) cfg.hm_cluster_size = std::stoi(value);
            }
        }
    }

    void args_config_client(int argc, char* argv[], config& cfg) {
        std::string arg, key, value;
        for(short i = 0; i < argc; i+=2) {
            arg = argv[i];
            if(argv[i][0] == '-' && argv[i][1] == '-') {
                key = arg.substr(2);
                value = argv[i+1];
            } else if(argv[i][0] == '-' && !argv[i][1] == '-') {
                key = arg.substr(1);
                value = argv[i+1];
            }
            if(key == 'h' || key == 'host') {
                if(::isdigit(value) && (value - '0' >= 0)) cfg.client_host = value;
            }
            if(key == 'p' || key == 'port') {
                if(::isdigit(value) && (value - '0' >= 0)) cfg.client_port = std::stoi(value);
            }
        }
    }
}