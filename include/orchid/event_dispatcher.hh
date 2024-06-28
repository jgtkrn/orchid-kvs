#ifndef 
#include<iostream>
#include<vector>
#include<sys/epoll.h>
typedef int EFD;
#define MAXEVCONN  0xF4240
#ifndef ORCHID_EVENT_DISPATCHER
#define ORCHID_EVENT_DISPATCHER
namespace orchid {
    class event_dispatcher {
        private:
            EFD fd;
            int nfds;
            short runner;
            std::vector<epoll_event> events;
        public:
            event_dispatcher();
            void init();
            bool attach_event();
            bool detach_event();
            int watch_event();
            EFD get_fd();
			void set_fd(EFD new_fd);
			short get_runner();
			void set_runner(short val);
            void close();
    }
    
}
#endif // ORCHID_EVENT_DISPATCHER