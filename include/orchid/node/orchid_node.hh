#include<string>

#ifndef ORCHID_NODE
#define ORCHID_NODE

namespace orchid {
	namespace node {
		/**
		* orchid_node struct
		* is an instance object
		* which suitable
		* for linked_list node,
		* containing orchid_entry sub data.
		*/
		struct orchid_node {
			std::string _key;
			std::string _value;
			orchid_node* _next;
			orchid_node(std::string key, std::string value): _key(key), _value(value), _next(nullptr) {}
		};
	}
}
#endif // ORCHID_NODE
