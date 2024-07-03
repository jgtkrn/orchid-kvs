#include<vector>
#include<functional>
#include<ds/linked_list.hh>
#include<ds/entry_node.hh>

#define DEFAULT_HMAP_CLUSTER_SIZE 16

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
             * _hash
             * operator object that return hash,
             * which will be used for key indexing.
             */
            std::hash<std::string> _hash;

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

        public:
            hash_map(unsigned long ht_size);
            /**
             * insert()
             * inserting new data to hash_map.
             */
            void insert(const std::string& key, const std::string& value);
            /**
             * remove()
             * removing data by it's key.
             */
            void remove(const std::string& key);
            /**
             * search()
             * search data by it's key.
             */
            std::string search(const std::string& key);
            /**
            * size()
            * return node count in hash map.
            */
            unsigned long size() const;
            /**
            * cluster_size()
            * return cluster count or hash table count in hash_map.
            */
            unsigned long cluster_size() const;
            ~hash_map();
    };
} // namespace ds
#endif // DS_HASH_MAP
