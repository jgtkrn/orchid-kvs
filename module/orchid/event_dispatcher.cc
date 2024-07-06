#include<orchid/event_dispatcher.hh>

namespace orchid {
        event_dispatcher::event_dispatcher(): _fd(-1), _runner(0), _nfds(0), _is_main_efd(true) {}
        void event_dispatcher::init() {
            EFD event_fd = jam_init();
            if(-1 == event_fd) {
                _runner = -1;
                std::cout << "Failed init event..." << std::endl;
            } else {
                _fd = event_fd;
            }
        }

        bool event_dispatcher::attach_event(const EFD& event_fd) {
            int event_ctl = jam_attach(_fd, event_fd, _is_main_efd);
            if(-1 == event_ctl) {
                std::cout << "Failed to attach event with efd: " << event_fd << std::endl;
            }
            _is_main_efd = false;
            return event_ctl > -1 ? true : false;
        }
        bool event_dispatcher::detach_event(const EFD& event_fd) {
            int event_ctl = jam_detach(_fd, event_fd);
            if(-1 == event_ctl) {
                std::cout << "Failed to detach event with efd: " << event_fd << std::endl;
            }
            return event_ctl > -1 ? true : false;
        }

        int event_dispatcher::watch_event() {
            _nfds = jam_watch(_fd, _events);
            if(-1 == _nfds) {
                _runner = -1;
                std::cout << "Failed watch events..." << std::endl;
            }
            return _nfds;
        }

        EFD event_dispatcher::get_fd() {
            return _fd;
        }

        void event_dispatcher::set_fd(const EFD& new_fd) {
            _fd = new_fd;
        }

        short event_dispatcher::get_runner() {
            return _runner;
        }

        void event_dispatcher::set_runner(const short& val) {
            _runner = val;
        }

        int event_dispatcher::get_nfds() {
            return _nfds;
        }

        EFD event_dispatcher::get_index_efd(const int& index) {
		#ifdef __linux__
            return _events[index].data.fd;
		#else
		return _events[index].ident;
		#endif
        }

        void event_dispatcher::close() {
            if(_fd > 0) ::close(_fd);
            _fd = -1;
        }
}
