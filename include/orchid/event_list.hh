#include<iostream>
typedef int EFD;
#ifndef ORCHID_EVENT_LIST
#define ORCHID_EVENT_LIST

namespace orchid {
	struct event_node {
		EFD fd;
		event_node* next;
		event_node(int fd): fd(fd), next(nullptr) {}
	}

	class event_list {
		public:
			unsigned long size;
			event_node* tail;
			
			event_list(): tail(nullptr), size(0) {}
			
			void attach(EFD fd) {
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
			
			void detach(event_node* node) {
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
	};
}
#endif // ORCHID_EVENT_LIST