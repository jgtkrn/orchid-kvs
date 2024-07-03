#include<string>

#ifndef CONFIG_DICTIONARY
#define CONFIG_DICTIONARY

/**
 * config dictionary
 * a struct containing any data
 * for orchid server needs.
 */
namespace config {
    struct dictionary {
        // hash_map data
        unsigned long hm_cluster_size;
        // socket data
        unsigned long socket_read_len;
        std::string server_host;
        std::string client_host;
        unsigned short client_port;
        unsigned short server_port;
    };
}
#endif // CONFIG_DICTIONARY
