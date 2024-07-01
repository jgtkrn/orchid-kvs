#include<ds/hash_map.hh>
namespace ds {
    template<HasNextPointer T>
    double hash_map<T>::_load_factor() {
        return static_cast<double>(_size) / _table.size();
    }
    
    template<HasNextPointer T>
    void hash_map<T>::_rehash() {
        std::vector<ds::linked_list<T>> new_table(_table.size() * 2);
        for (auto& list : _table) {
            T* _current = list._tail;
            while (_current) {
                size_t new_index = _hash(_current->_key) % new_table.size();
                T* next = _current->_next;
                _current->_next = nullptr;
                new_table[new_index].attach(_current);
                _current = next;
            }
        }
        _table.swap(new_table);
    }

    template<HasNextPointer T>
    hash_map<T>::hash_map(unsigned long ht_size): _table(ht_size), _size(0);
    
    template<HasNextPointer T>
    void hash_map<T>::insert(std::string& key, std::string& value) {
        unsigned long index = _hash(key) % _table.size();
        T* node = new T{key, value, nullptr};
        _table[index].attach(node);
        _size++;
        if (_loadFactor() > 0.7) {
            _rehash();
        }
    }
    
    template<HasNextPointer T>
    void hash_map<T>::remove(std::string& key) {
        unsigned long index = _hash(key) % _table.size();
        _table[index].detach(key);
        _size--;
    }

    template<HasNextPointer T>
    T* hash_map<T>::search(std::string& key) {
        unsigned long index = _hash(key) % _table.size();
        T* node = _stable[index].search(key);
        if (node) {
            return &(node->value);
        }
        return nullptr;
    }
}