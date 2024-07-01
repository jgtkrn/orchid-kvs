#include<vector>
#include<functional>
#include<ds/linked_list.hh>
#include<ds/entry_node.hh>

#ifndef DS_HASH_MAP
#define DS_HASH_MAP
namespace ds {
    /**
     * hash_map class
     * just a typical hash map object which using
     * chaining method to handle collisions.
     */
    class hash_map {
        private:
            /**
             * _table
             * container for node object which storing
             * client request data, usually contained
             * key and value.
             */
            std::vector<ds::linked_list> _table;

            /**
             * _size
             * as usual, it's just size of this hash_map.
             */
            unsigned long _size;

            /**
             * _load_factor()
             * returns indicator for rehashing hash_map.
             */
            double _load_factor();

            /**
             * _rehash()
             * rearrange hash_map if the size exceed the load factor.
             */
            void _rehash();

            /**
             * _hash
             * operator object that return hash,
             * which will be used for key indexing.
             */
            std::hash<std::string> _hash;

        public:
            hash_map(unsigned long ht_size);
            /**
             * insert()
             * inserting new data to hash_map.
             */
            void insert(std::string& key, std::string& value);
            /**
             * remove()
             * removing data by it's key.
             */
            void remove(std::string& key);
            /**
             * search()
             * search data by it's key.
             */
            std::string search(std::string& key);
    };
} // namespace ds
#endif // DS_HASH_MAP
