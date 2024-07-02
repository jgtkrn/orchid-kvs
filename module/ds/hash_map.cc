#include<ds/hash_map.hh>
namespace ds {
    double hash_map::_load_factor() {
        return static_cast<double>(_size) / _table.size();
    }

    void hash_map::_rehash() {
        std::vector<ds::linked_list> new_table(_table.size() * 2);
        for (auto& list : _table) {
            ds::entry_node* _current = list._tail;
            while (_current) {
                size_t new_index = _hash(_current->_key) % new_table.size();
                ds::entry_node* next = _current->_next;
                _current->_next = nullptr;
                new_table[new_index].attach(_current);
                _current = next;
            }
        }
        _table.swap(new_table);
    }

    hash_map::hash_map(unsigned long ht_size): _table(ht_size), _size(0) {}

    void hash_map::insert(std::string& key, std::string& value) {
        unsigned long index = _hash(key) % _table.size();
        ds::entry_node* exists_node = _table[index].search(key);
        if (exists_node) {
		exists_node->_value = value;
            return;
        }
	ds::entry_node* node = new ds::entry_node(key, value);
        _table[index].attach(node);
        _size++;
        if (_load_factor() > 0.7) {
            _rehash();
        }
    }

    void hash_map::remove(std::string& key) {
        unsigned long index = _hash(key) % _table.size();
        if(_table[index].detach(key)) {
	        _size--;
	}
    }

    std::string hash_map::search(std::string& key) {
        unsigned long index = _hash(key) % _table.size();
        ds::entry_node* node = _table[index].search(key);
        if (node) {
            return node->_value;
        }
	std::string nf = "Not Found";
        return nf;
    }
	unsigned long hash_map::size() {
		return _size;
	}
	unsigned long hash_map::cluster_size() {
		return _table.size();
	}
	hash_map::~hash_map() {
		for(ds::linked_list list: _table) {
			list.close();
		}
	}
}

