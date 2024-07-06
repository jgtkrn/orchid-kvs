#ifdef __linux__
#include <orchid/jam/epoll.hh>
using namespace orchid::jam::epoll;
#else
#include <orchid/jam/kqueue.hh>
using namespace orchid::jam::kqueue;
#endif

#ifndef ORCHID_EVENT_DISPATCHER
#define ORCHID_EVENT_DISPATCHER

/**
 * event_dispatcher class
 * event management object, to manage sockets file descriptor
 * using multiplexing method, so there still possibly single threaded
 * operations for sockets management.
 */
namespace orchid {
    class event_dispatcher {
        private:
            /**
			 * _fd is a variable to store event dispatcher file descriptor. 
			 * returns -1 if event dispatcher failed to initialize and greater than
			 * 0 (commonly above 2 outside std fd).
			 */
			EFD _fd;

			/**
			 * _runner is an indicator to check whether this event dispatcher 
			 * need to be closed. returns -1 if this event dispatcher gain issue, 
			 * and 0 if no issue that require this event dispatcher closed.
			 */
			short _runner;

            /**
             * _nfds is a variable to store 'n' count of file descriptors registered
             * to current event dispatcher object.
             */
            int _nfds;

            /**
             * _is_main_efd is an indicator to manage event flags between main
             * event file descriptor, and incoming events file descriptor.
             */
            bool _is_main_efd;

            /**
             * _events is a stack of event registered in current
             * event dispatcher, to be managed later by the watcher.
             */
            #ifdef __linux__
            struct epoll_event _events[MAXEVCONN];
            #else
            struct kevent _events[MAXEVCONN];
            #endif
        public:
            event_dispatcher();
            /**
			 * init()
			 * event dispatcher function to initialize event dispatcher class
			 * contains file descriptor '_fd' generation
			 * through event dispatcher initialization.
			 */
            void init();

            /**
             * attach_event()
             * attach incoming event to current event dispatcher.
             */
            bool attach_event(const EFD& event_fd);

            /**
             * detach_event()
             * detach existing event in current event dispatcher.
             */
            bool detach_event(const EFD& event_fd);

            /**
             * watch_event()
             * manage registered events file descriptor
             * in _t_events stack, for operation later.
             * returns number of event triggered.
             */
            int watch_event();

            /**
			 * get_fd()
			 * returns initialized event dispatcher file descriptor.
			 */
			EFD get_fd();

			/**
			 * set_fd()
			 * file descriptor setter for current event dispatcher.
			 */
			void set_fd(const EFD& new_fd);

			/**
			 * get_runner()
			 * getter for _runner value.
			 */
			short get_runner();

			/**
			 * set_runner()
			 * setter for _runner value.
			 */
			void set_runner(const short& val);

            /**
             * get_nfds()
             * returns 'n' count of file descriptors 
             * registered in current event dispatcher object.
             */
            int get_nfds();

            /**
             * get_index_efd()
             * returns file descriptors in current 
             * event dispatcher object by index specified.
             */
            EFD get_index_efd(const int& index);

			/**
			 * close()
			 * release file descriptor which assigned to current socket
			 */
            void close();
    };
}
#endif // ORCHID_EVENT_DISPATCHER
