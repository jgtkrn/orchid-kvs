#include<orchid/event_dispatcher.hh>

namespace orchid {
        event_dispatcher::event_dispatcher(): fd(-1), nfds(0), runner(0) {}
        void event_dispatcher::init() {
            EFD event_fd = ::epoll_create1(0);
            if(-1 == event_fd) {
                set_runner(-1);
                std::cout << "Failed init epoll..." << std::endl;
            } else {
                set_fd(event_fd);
                std::cout << "Success init epoll, with efd: " << event_fd << std::endl;
            }
        }

        bool event_dispatcher::attach_event(EFD event_fd) {
            struct epoll_event ev;
            ev.events = EPOLLIN;
            ev.data.fd = event_fd;
            int event_ctl = epoll_ctl(get_fd(), EPOLL_CTL_ADD, event_fd, &ev);
            if(-1 == event_ctl) {
                std::cout << "Failed to attach event with efd: " << event_fd << std::endl;
            }
            return event_ctl > -1 ? true : false;
        }
        bool event_dispatcher::detach_event(EFD event_fd) {
            struct epoll_event ev;
            ev.events = EPOLLIN;
            ev.data.fd = event_fd;
            int event_ctl = epoll_ctl(get_fd(), EPOLL_CTL_ADD, event_fd, &ev);
            if(-1 == event_ctl) {
                std::cout << "Failed to attach event with efd: " << event_fd << std::endl;
            }
            return event_ctl > -1 ? true : false;
        }
        int event_dispatcher::watch_event() {
            nfds = epoll_wait(get_fd(), events, MAXEVCONN, -1);
            if(-1 == nfds) {
                std::cout << "No events to watch " << std::endl;
            }
            return nfds;
        }

        EFD event_dispatcher::get_fd() {
            return fd;
        }
        void event_dispatcher::set_fd(EFD new_fd) {
            fd = new_fd;
        }
        short event_dispatcher::get_runner() {
            return runner;
        }
        void event_dispatcher::set_runner(short val) {
            runner = val;
        }
        void event_dispatcher::close() {
            ::close(get_fd());
        }
}
