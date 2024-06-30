#include <sstream>
#include <vector>
#include <string>
#include <ctype.h>

namespace orchid {
    namespace marshall {

        /**
        * orchid_string
        * is a string sequence with spesific format,
        * which will help orhid-kvs server to parse command from the client.
        *
        * Format:
        * #(length of command)\r\n$(length of string)\r\n(string of command)\r\n
        *
        * Example:
        * Command: SET NAME USER
        * #3\r\n$3\r\nSET\r\n$4\r\nNAME\r\n$4\r\nuser\r\n
        *
        * Parse:
        * - #3 means the command has length of three
        * - $3 the first command has length of three characters
        * - $4 the second command has length of four characters
        * - $3 the third command has length of three characters
        *
        * Meanwhile the whitespaces \r\n act like delimiter to ease string tokenization.
        */
        typedef std::string orchid_string;

        /**
         * orchid_entry
         * is struct of strings, which is result of unmarsalling
         * orchid_string input. orchid_entry contains integer of
         * command length, string of command, string of key, and
         * string of value.
         */
        struct orchid_entry {
            int command_length;
            std::string command;
            std::string key;
            std::string value;
        };

        /**
         * validate_format()
         * as it's name this function act as orchid_string
         * format validation before processed later.
         */
        bool validate_format(orchid_string& orchid_string);

        /**
         * tear_string()
         * a function to split string to vector of string.
         */
        std::vector<std::string> tear_string(std::string &str);

        /**
         * marshall_to()
         * is a function to convert regular string to orchid_string format.
         */
        orchid_string marshall_from(std::string& message);

        /**
         * unmarshall_to()
         * is a function to convert orchid_string to orchid_entry
         */
        orchid_entry unmarshall_from(orchid_string& orchid_string);

        /**
         * NOTE: seek through data flow from client to orchid-kvs server
         * client regular string -> orchid_string -> orchid_entry -> orchid-kvs server
         */
    } // namespace marshall
} // namespace orchid
