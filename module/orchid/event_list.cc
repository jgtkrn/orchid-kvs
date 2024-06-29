#include<orchid/event_list.hh>
namespace orchid {
    event_list::event_list() : tail(nullptr), size(0) {}
    void event_list::attach(EFD fd) {
        event_node* new_node = new event_node(fd);
        if (!head) {
            head = new_node;
            size++;
            return;
        }
        event_node* temp = tail;
        new_node->next = temp;
        tail = new_node;
        size++;
    }
    void event_list::detach(event_node* node) {
        if (!node || !tail) return;

        if (node == tail) {
            tail = tail->next;
            delete node;
            size--;
            return;
        }

        event_node* prev = tail;
        while (prev->next && prev->next != node) {
            prev = prev->next;
        }

        if (prev->next == nullptr) {
            return;
        }

        prev->next = node->next;
        delete node;
        size--;
    }
}