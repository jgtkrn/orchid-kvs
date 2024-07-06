#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <orchid/jam/macro_init.hh>

namespace orchid::jam::epoll {
    EFD jam_init();
    int jam_attach(const EFD& epfd, const const EFD& event_fd);
    int jam_detach(const EFD& epfd, const const EFD& event_fd);
    int jam_watch(const EFD& epfd, epoll_event events[]);
}
