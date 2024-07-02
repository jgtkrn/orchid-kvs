#include<string>

#ifndef CONFIG_DICTIONARY
#define CONFIG_DICTIONARY

/**
 * config dictionary
 * a struct containing any data
 * for orchid server needs.
 */
namespace orc_config {
    struct dictionary {
        // socket data
        std::string server_host;
        unsigned long server_port;
        std::string client_host;
        unsigned long client_port;
        int socket_read_len;

        // hash_map data
        unsigned long hm_cluster_size;
    };
}
#endif // CONFIG_DICTIONARY
