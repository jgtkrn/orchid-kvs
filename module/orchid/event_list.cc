#include<orchid/event_list.hh>
namespace orchid {
    event_list::event_list(): _tail(nullptr), _size(0) {}
    void event_list::attach(EFD fd) {
        event_node* new_node = new event_node(fd);
        if (!tail) {
            _tail = new_node;
            _size++;
            return;
        }
        event_node* temp = _tail;
        new_node->next = temp;
        tail = new_node;
        size++;
    }
    void event_list::detach(event_node* node) {
        if (!node || !_tail) return;

        if (node == _tail) {
            _tail = _tail->next;
            delete node;
            _size--;
            return;
        }

        event_node* prev = _tail;
        while (prev->next && prev->next != node) {
            prev = prev->next;
        }

        if (prev->next == nullptr) {
            return;
        }

        prev->next = node->next;
        delete node;
        _size--;
    }
}
