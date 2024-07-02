#include<orchid/marshall.hh>
#include<iostream>
namespace orchid {
    namespace marshall {

        bool validate_format(orchid_string& orchid_string) {
            return orchid_string[0] == '#' && ::isdigit(orchid_string[1]) && ((orchid_string[1] - '0') == 2 || (orchid_string[1] - '0') == 3) && orchid_string[2] == '\r' && orchid_string[3] == '\n';
        }

        std::vector<std::string> tear_string(std::string& str) {
            std::istringstream stream(str);
            std::vector<std::string> tokens;
            std::string token;
		for (int i = 0; i < 2; ++i) {
        		if (stream >> token) {
            		tokens.push_back(token);
        		}
    		}
		std::string remainder;
    		std::getline(stream, remainder);
   		if (!remainder.empty() && remainder[0] == ' ') {
        		remainder.erase(0, 1);
    		}
    		if(remainder.size() > 0) tokens.push_back(remainder);
            return tokens;
        }

        orchid_string marshall_from(std::string& message) {
            std::vector<std::string> tokens = tear_string(message);
            std::ostringstream stream;
            stream << "#" << tokens.size() << "\r\n";
            for (auto &token : tokens) {
                stream << "$" << token.size() << "\r\n" << token << "\r\n";
            }
            orchid_string oc_str = stream.str();
            return oc_str;
        }

        orchid_entry unmarshall_from(orchid_string& orchid_string) {
            struct orchid_entry entry;
	int index = 0;
    	int command_length;
    	std::string cl_str;
    	if(orchid_string[index] == '#') command_length = std::stoi(cl_str + orchid_string[index + 1]);
    	index += 4;
    	std::string shards[command_length];
	    for (int i= 0; i < command_length; i++) {
	      if(orchid_string[index] == '$') {
        	  index++;
          	std::string cmd_str;
          	while (::isdigit(orchid_string[index])) {
              		cmd_str += orchid_string[index];
              		index++;
          	}
          	int cmd_length = std::stoi(cmd_str);
          	index += 2;
          	std::string command = orchid_string.substr(index, cmd_length);
          	shards[i] = command;
          	if(i != command_length - 1) index += cmd_length + 2;
      		}
    	}
    		entry.command = shards[0];
   		 entry.key = shards[1];
    		entry.value = command_length == 3 ? shards[2] : "";
		return entry;
        }
    } // namespace marshall
} // namespace orchid
