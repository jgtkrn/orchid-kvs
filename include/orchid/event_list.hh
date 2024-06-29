#include<iostream>
typedef int EFD;
#ifndef ORCHID_EVENT_LIST
#define ORCHID_EVENT_LIST

namespace orchid {
	struct event_node {
		EFD fd;
		event_node* next;
		event_node(int fd): fd(fd), next(nullptr) {}
	};

	class event_list {
		public:
			unsigned long size;
			event_node* tail;
			event_list();
			void attach(EFD fd);
			void detach(event_node* node);
	};
}
#endif // ORCHID_EVENT_LIST
