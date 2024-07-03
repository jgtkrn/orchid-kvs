#include<orchid/event_dispatcher.hh>

namespace orchid {
        event_dispatcher::event_dispatcher(): _fd(-1), _runner(0), _nfds(0), _is_main_efd(true) {}
        void event_dispatcher::init() {
            EFD event_fd = ::epoll_create1(0);
            if(-1 == event_fd) {
                set_runner(-1);
                std::cout << "Failed init epoll..." << std::endl;
            } else {
                set_fd(event_fd);
            }
        }

        bool event_dispatcher::attach_event(EFD event_fd) {
            struct epoll_event ev;
            ev.events = _is_main_efd ? EPOLLIN : EPOLLIN | EPOLLET;
            ev.data.fd = event_fd;
            int event_ctl = epoll_ctl(get_fd(), EPOLL_CTL_ADD, event_fd, &ev);
            if(-1 == event_ctl) {
                std::cout << "Failed to attach event with efd: " << event_fd << std::endl;
            }
            _is_main_efd = false;
            return event_ctl > -1 ? true : false;
        }
        bool event_dispatcher::detach_event(EFD event_fd) {
            int event_ctl = epoll_ctl(get_fd(), EPOLL_CTL_DEL, event_fd, NULL);
            if(-1 == event_ctl) {
                std::cout << "Failed to detach event with efd: " << event_fd << std::endl;
            }
            return event_ctl > -1 ? true : false;
        }

        int event_dispatcher::watch_event() {
            _nfds = epoll_wait(get_fd(), _events, MAXEVCONN, 0);
            if(-1 == _nfds) {
                set_runner(-1);
                std::cout << "Failed watch events..." << std::endl;
            }
            return _nfds;
        }

        EFD event_dispatcher::get_fd() {
            return _fd;
        }

        void event_dispatcher::set_fd(EFD new_fd) {
            _fd = new_fd;
        }

        short event_dispatcher::get_runner() {
            return _runner;
        }

        void event_dispatcher::set_runner(short val) {
            _runner = val;
        }

        int event_dispatcher::get_nfds() {
            return _nfds;
        }

        EFD event_dispatcher::get_index_efd(int index) {
            return _events[index].data.fd;
        }

        void event_dispatcher::close() {
		if(_fd > 0) ::close(_fd);
		_fd = -1;
        }
}
