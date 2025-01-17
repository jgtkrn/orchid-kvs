#include<ds/linked_list.hh>
namespace ds {
    linked_list::linked_list(): _size(0), _tail(nullptr) {}

	void linked_list::attach(ds::entry_node* node) {
        if (!_tail) {
            _tail = node;
            _size++;
            return;
        }
        node->_next = _tail;
        _tail = node;
        _size++;
    }

	bool linked_list::detach(const std::string& key) {
        ds::entry_node* _current = _tail;
        ds::entry_node* _previous = nullptr;
        while (_current) {
            if (_current->_key == key) {
                if (_previous) {
                    _previous->_next = _current->_next;
                } else {
                    _tail = _current->_next;
                }
                delete _current;
                _size--;
                return true;
            }
            _previous = _current;
            _current = _current->_next;
        }
	return false;
    }

    ds::entry_node* linked_list::search(const std::string& key) {
        ds::entry_node* _current = _tail;
        while (_current) {
            if (_current->_key == key) {
                return _current;
            }
            _current = _current->_next;
        }
        return nullptr;
    }
	void linked_list::close() {
		ds::entry_node* current = _tail;
        	while (current != nullptr) {
            		ds::entry_node* to_delete = current;
            		current = current->_next;
            		delete to_delete;
			_size--;
        	}
	}
}
