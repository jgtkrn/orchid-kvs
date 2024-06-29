#include<iostream>
#include<sys/epoll.h>
#include<unistd.h>
#include<errno.h>
typedef int EFD;
#define MAXEVCONN 500000
#ifndef ORCHID_EVENT_DISPATCHER
#define ORCHID_EVENT_DISPATCHER
namespace orchid {
    class event_dispatcher {
        private:
            EFD fd;
            int nfds;
            short runner;
            bool is_main_efd;
        public:
            struct epoll_event events[MAXEVCONN];
            event_dispatcher();
            void init();
            bool attach_event(EFD event_fd);
            bool detach_event(EFD event_fd);
            int watch_event();
            EFD get_fd();
		    void set_fd(EFD new_fd);
		    short get_runner();
		    void set_runner(short val);
            int get_nfds();
            EFD get_index_efd(int index);
            void close();
    };
}
#endif // ORCHID_EVENT_DISPATCHER
