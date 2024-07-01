#include<iostream>
#include<string>
#include<concepts>

#ifndef DS_LINKED_LIST
#define DS_LINKED_LIST

namespace ds {
    /**
     * this template define to rule the type used
     * for this linked_list class, the struct used
     * should have _next instance which is pointer
     * to their own type.
     */
    template<typename T>
    concept HasNextPointer = requires(T t) {
        { t._next } -> std::same_as<T*>;
    };

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
    template<HasNextPointer T>
	class linked_list {
		public:
			/**
			 * represent current size of linked_list.
			 */
			unsigned long _size;

			/**
			 * tail is the latest node
			 */
			T* _tail;
			linked_list();

			/**
			 * attach()
			 * initalize new node from file descriptor specified
			 * and attach it to linked_list tail.
			 */
			void attach(T* node);

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
            T* search(std::string& key);
	};
} // namespace ds
#endif // DS_LINKED_LIST