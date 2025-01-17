#include <orchid/jam/epoll.hh>
namespace orchid::jam::epoll {
    EFD jam_init() {
        EFD efd = ::epoll_create1(0);
        return efd;
    }
    int jam_attach(const EFD& epfd, const EFD& event_fd, bool _is_main_efd = false) {
        struct epoll_event ev;
        ev.events = _is_main_efd ? EPOLLIN : EPOLLIN | EPOLLET;
        ev.data.fd = event_fd;
        return ::epoll_ctl(epfd, EPOLL_CTL_ADD, event_fd, &ev);
    }

    int jam_detach(const EFD& epfd, const EFD& event_fd) {
        return ::epoll_ctl(epfd, EPOLL_CTL_DEL, event_fd, NULL);
    }

    int jam_watch(const EFD& epfd, struct epoll_event events[]) {
        return ::epoll_wait(epfd, events, MAXEVCONN, 0);
    }
}
