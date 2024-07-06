/**
 * redefine int as EFD for easier reading, since file descriptor is an integer.
 */
typedef int EFD;

/**
 * initial limit for epoll event stack, it is depend on every OS limitation.
 */
#define MAXEVCONN 100000