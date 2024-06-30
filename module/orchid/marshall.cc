#include<orchid/marshall.hh>

namespace orchid {
    namespace marshall {

        bool validate_format(orchid_string& orchid_string) {
            return orchid_string[0] == '#' && ::isdigit(orchid_string[1]) && orchid_string[2] == '\r' && orchid_string[3] == '\n';
        }

        std::vector<std::string> tear_string(std::string &str) {
            std::istringstream stream(str);
            std::vector<std::string> tokens;
            std::string token;
            while (stream >> token) {
                tokens.push_back(token);
            }
            return tokens;
        }

        orchid_string marshall::marshall_from(std::string& message) {
            std::vector<std::string> tokens = tear_string(message);
            std::ostringstream stream;
            stream << "#" << tokens.size() << "\r\n";
            for (auto &token : tokens) {
                stream << "$" << token.size() << "\r\n" << token << "\r\n";
            }
            orchid_string oc_str = stream.str()
            return oc_str;
        }

        struct orchid_entry marshall::unmarshall_from(orchid_string& orchid_string) {
            struct orchid_entry entry;
            int command_length = orchid_string[1] - '0';
            int next_msg = 4;
            int substr_length;
            std::vector<std::string> command_shards;
            for(int i = 0; i < command_length; ++i) {
                if('$' == orchid_string[next_msg]) {
                    next_msg++;
                    substr_length = orchid_string[next_msg] - '0';
                    next_msg += 3;
                    command_shards.push_back(orchid_string.substr(next_msg, substr_length));
                    if(command_length - 1 != i) next_msg += substr_length + 2;
                }
            }
            if(command_length == 2 || command_length == 3) {
                entry.command_length = command_length;
                entry.command = command_shards[0] ? command_shards[0] : "";
                entry.key = 3 == command_length ? command_shards[0] : "";
                entry.value = 3 == command_length ? command_shards[2] : command_shards[1];
            } else {
                entry.command_length = command_length;
                entry.command = "";
                entry.key = "";
                entry.value = "";
            }
            return entry;
        }
    } // namespace marshall
} // namespace orchid