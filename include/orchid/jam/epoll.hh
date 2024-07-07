#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <orchid/jam/macro_init.hh>

/**
 * epoll
 * is used to manage event
 * in linux based OS.
 */
namespace orchid::jam::epoll {
    /**
     * jam_init()
     * initialize event jam.
     */
    EFD jam_init();
    
    /**
     * jam_attach()
     * add new event to events stack.
     */
    int jam_attach(const EFD& epfd, const EFD& event_fd, bool _is_main_efd);
        
    /**
     * jam_detach()
     * remove event to events stack.
     */
    int jam_detach(const EFD& epfd, const EFD& event_fd);
    
    /**
     * jam_watch()
     * initialize event watcher, to check whether
     * there are events to be handled.
     */
    int jam_watch(const EFD& epfd, struct epoll_event events[]);
}
