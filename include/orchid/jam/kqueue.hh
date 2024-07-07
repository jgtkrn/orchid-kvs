#include <iostream>
#include <sys/event.h>
#include <unistd.h>
#include <errno.h>
#include <orchid/jam/macro_init.hh>

namespace orchid::jam::kqueue {
    EFD jam_init();
    int jam_attach(const EFD& epfd, const EFD& event_fd, struct kevent r_events[]);
    int jam_detach(const EFD& epfd, const EFD& event_fd, struct kevent r_events[]);
    int jam_watch(const EFD& epfd, struct kevent events[]);
}
