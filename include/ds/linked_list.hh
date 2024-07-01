#include<iostream>
#include<string>
#include<ds/ds::entry_node.hh>

#ifndef DS_LINKED_LIST
#define DS_LINKED_LIST

namespace ds {
	/**
	 * linked_list class
	 * object created to manage data which pushed by clients.
	 * linked_list class using singly linked list, to manage
	 * lower memory usage overhead, cause this model only need
	 * one pointer for each node.
	 *
	 * linked_list class also optimized for node insertion.
	 * data order is using LIFO, so we only need O(1)
	 * time complexity for inserting new node.
	 */
	class linked_list {
		public:
			/**
			 * represent current size of linked_list.
			 */
			unsigned long _size;

			/**
			 * tail is the latest node
			 */
			ds::entry_node* _tail;
			linked_list();

			/**
			 * attach()
			 * initalize new node from file descriptor specified
			 * and attach it to linked_list tail.
			 */
			void attach(ds::entry_node* node);

			/**
			 * detach()
			 * remove node by a key speficied from 
			 * current linked_list and rearrange linked_list.
			 */
			void detach(std::string& key);

            /**
             * search()
             * find any value from a key specificed.
             */
            ds::entry_node* search(std::string& key);
	};
} // namespace ds
#endif // DS_LINKED_LIST
