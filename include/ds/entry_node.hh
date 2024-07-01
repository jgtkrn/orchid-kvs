#include<string>

#ifndef ENTRY_NODE
#define ENTRY_NODE

namespace ds {
    /**
    * entry_node struct
    * is an instance object
    * which suitable
    * for linked_list node,
    * containing entry_entry sub data.
    */
    struct entry_node {
        std::string _key;
        std::string _value;
        entry_node* _next;
        entry_node(std::string key, std::string value): _key(key), _value(value), _next(nullptr) {}
    };
}
#endif // ENTRY_NODE
