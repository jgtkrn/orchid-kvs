#include<iostream>

/**
 * redefine int as EFD for easier reading, since file descriptor is an integer.
 */
typedef int EFD;

#ifndef ORCHID_EVENT_LIST
#define ORCHID_EVENT_LIST

namespace orchid {
	/**
	 * event_node struct
	 * is an instance object
	 * for event_list node.
	 */
	struct event_node {
		EFD _fd;
		event_node* _next;
		event_node(int fd): _fd(fd), _next(nullptr) {}
	};

	/**
	 * event_list class
	 * object created to manage file descriptor externaly
	 * outside event dispatcher. event_list is actually designed
	 * to manage gracefull shutdown and closed event,
	 * but maybe there are some benefit discovered in the future.
	 *
	 * event_list class using singly linked list, to manage
	 * lower memory usage overhead, cause this model only need
	 * one pointer for each node.
	 *
	 * event_list class also optimized for node insertion.
	 * the model is reversed, so the top is actually a tail,
	 * or latest node, so we only need O(1) time complexity
	 * for inserting new node.
	 */
	class event_list {
		public:
			/**
			 * represent current size of event_list.
			 */
			unsigned long _size;

			/**
			 * tail is the latest node
			 */
			event_node* _tail;
			event_list();

			/**
			 * attach()
			 * initalize new node from file descriptor specified
			 * and attach it to event_list tail.
			 */
			void attach(EFD fd);

			/**
			 * detach()
			 * remove speficied node from curent event_list
			 * and rearrange event list.
			 */
			void detach(event_node* node);
	};
}
#endif // ORCHID_EVENT_LIST
