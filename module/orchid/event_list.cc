#include<orchid/event_list.hh>
namespace orchid {
    event_list::event_list(): _size(0), _tail(nullptr) {}
    void event_list::attach(EFD fd) {
        event_node* new_node = new event_node(fd);
        if (!_tail) {
            _tail = new_node;
            _size++;
            return;
        }
        event_node* temp = _tail;
        new_node->_next = temp;
        _tail = new_node;
        _size++;
    }
    void event_list::detach(event_node* node) {
        if (!node || !_tail) return;

        if (node == _tail) {
            _tail = _tail->_next;
            delete node;
            _size--;
            return;
        }

        event_node* prev = _tail;
        while (prev->_next && prev->_next != node) {
            prev = prev->_next;
        }

        if (prev->_next == nullptr) {
            return;
        }

        prev->_next = node->_next;
        delete node;
        _size--;
    }
}
