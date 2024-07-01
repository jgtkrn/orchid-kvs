#include<ds/linked_list.hh>
namespace ds {
    template<HasNextPointer T>
    linked_list<T>::linked_list(): _size(0), _tail(nullptr) {}

    template<HasNextPointer T>		
	void linked_list<T>::attach(T* node) {
        if (!_tail) {
            _tail = node;
            _size++;
            return;
        }
        node->_next = _tail;
        _tail = node;
        _size++;
    }

    template<HasNextPointer T>
	void linked_list<T>::detach(std::string& key) {
        T* _current = _tail;
        T* _previous = nullptr;
        while (_current) {
            if (_current->_key == key) {
                if (_previous) {
                    _previous->_next = _current->_next;
                } else {
                    _tail = _current->_next;
                }
                delete _current;
                _size--;
                return;
            }
            _previous = _current;
            _current = _current->_next;
        }
    }

    template<HasNextPointer T>
    T* linked_list<T>::search(std::string& key) {
        T* _current = _tail;
        while (_current) {
            if (_current->_key == key) {
                return _current;
            }
            _current = _current->_next;
        }
        return nullptr;
    }
}