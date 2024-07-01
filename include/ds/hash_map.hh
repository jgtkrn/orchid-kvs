#include<vector>
#include<functional>
#include<concepts>
#include<ds/linked_list.hh>

#ifndef DS_HASH_MAP
#define DS_HASH_MAP
namespace ds {
    /**
     * this template define to rule the type used
     * for this hash_map class, the struct used
     * should have _next instance which is pointer
     * to their own type.
     */
    template<typename T>
    concept HasNextPointer = requires(T t) {
        { t._next } -> std::same_as<T*>;
    };

    /**
     * hash_map class
     * just a typical hash map object which using
     * chaining method to handle collisions.
     */
    template<HasNextPointer T>
    class hash_map {
        private:
            /**
             * _table
             * container for node object which storing
             * client request data, usually contained
             * key and value.
             */
            std::vector<ds::linked_list<T>> _table;

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
    }
} // namespace ds
#endif // DS_HASH_MAP