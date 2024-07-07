#include <iostream>
#include <sys/event.h>
#include <unistd.h>
#include <errno.h>
#include <orchid/jam/macro_init.hh>

/**
 * kqueue
 * is used to manage event
 * in bsd based OS.
 */
namespace orchid::jam::kqueue {
    /**
     * jam_init()
     * initialize event jam.
     */
    EFD jam_init();

    /**
     * jam_attach()
     * add new event to events stack.
     */
    int jam_attach(const EFD& epfd, const EFD& event_fd, struct kevent r_events[]);
    
    /**
     * jam_detach()
     * remove event to events stack.
     */
    int jam_detach(const EFD& epfd, const EFD& event_fd, struct kevent r_events[]);

    /**
     * jam_watch()
     * initialize event watcher, to check whether
     * there are events to be handled.
     */
    int jam_watch(const EFD& epfd, struct kevent events[]);
}
