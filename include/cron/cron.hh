#include <unistd.h>
#include <ctype.h>
#include <thread>
#include <functional>
#include <string>
#include <iostream>

#ifndef CRON_SCHEDULER
#define CRON_SCHEDULER

namespace cron {
    long long time_mapper(std::string time);
    void schedule(std::string time, std::function<void()> func);
}

#endif // CRON_SCHEDULER