#include <unistd.h>
#include <ctype.h>
#include <thread>
#include <functional>
#include <string>
#include <iostream>

#ifndef CRON_SCHEDULER
#define CRON_SCHEDULER

/**
 * cron
 * is namespace for any
 * scheduling purpose functions.
 */
namespace cron {
    /**
     * time_mapper()
     * takes string of time within this format
     * D or d is suffix for day count time
     * H or h is suffix for hour count time
     * M or m is suffix for minute count time
     * S or s is suffix for second count time
     * MS or ms is suffix for millisecond count time
     * US or us is suffix for microsecond count time
     * example: 2d3h4m1s5ms300us
     * represents 2 days, 3 hours, 4 minutes, 1 seconds,
     * 5 milliseconds, and 300 microseconds.
     */
    long long time_mapper(std::string time);

    /**
     * schedule()
     * schedule to execute a function
     * every 'time' specified which
     * is refer to time_mapper().
     */
    void schedule(std::string time, std::function<void()> func);
}

#endif // CRON_SCHEDULER