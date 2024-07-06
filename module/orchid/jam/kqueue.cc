#include <orchid/jam/kqueue.hh>
namespace orchid::jam::kqueue {
    EFD jam_init() {
        EFD efd = ::kqueue();
        return efd;
    }

    int jam_attach(const EFD& epfd, const EFD& event_fd) {
        struct kevent ev;
        EV_SET(&ev, event_fd, EVFILT_VNODE, EV_ADD | EV_ENABLE, NOTE_READ | NOTE_WRITE, 0, NULL);
        int ctl = ::kevent(epfd, &ev, 1, NULL, 0, NULL);
        return ctl;
    }

    int jam_detach(const EFD& epfd, const EFD& event_fd) {
        struct kevent ev;
        EV_SET(&ev, event_fd, EVFILT_EMPTY, EV_DELETE | EV_DISABLE, NULL, 0, NULL);
        int ctl = ::kevent(epfd, &ev, 1, NULL, 0, NULL);
        return ctl;
    }
    int jam_watch(const EFD& epfd, struct kevent events[]) {
        int nfds = kevent(epfd, NULL, 0, events, MAXEVCONN, NULL);
        return nfds;
    }
}
