#include <orchid/jam/kqueue.hh>
namespace orchid::jam::kqueue {
    EFD jam_init() {
        return ::kqueue();
    }

    int jam_attach(const EFD& epfd, const EFD& event_fd, struct kevent r_events[]) {
        EV_SET(r_events, event_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
        return ::kevent(epfd, r_events, 1, NULL, 0, NULL);
    }

    int jam_detach(const EFD& epfd, const EFD& event_fd,struct kevent r_events[]) {
        EV_SET(r_events, event_fd, EVFILT_EMPTY, EV_DELETE | EV_DISABLE, 0, 0, 0);
        return ::kevent(epfd, r_events, 1, NULL, 0, NULL);
    }
    int jam_watch(const EFD& epfd, struct kevent events[]) {
        return ::kevent(epfd, NULL, 0, events, 1, NULL); 
    }
}
