#include <cron/cron.hh>

namespace cron {
    long long time_mapper(std::string time) {
        useconds_t minutes = 0;
        useconds_t seconds = 0;

        unsigned long s_t = 1000000;
        unsigned long m_t = s_t * 60;

        std::string temp_time_string = "";

        for(unsigned long i = 0; i < time.size(); ++i) {
            if(::isdigit(time[i])) {
                temp_time_string += time[i];
            } else {
                if(time[i] == 'M' || time[i] == 'm') {
                    minutes += (std::stoul(temp_time_string) * m_t);
                    temp_time_string = "";
                } else if(time[i] == 'S' || time[i] == 's') {
                    seconds += (std::stoul(temp_time_string) * s_t);
                    temp_time_string = "";
                } else {
                    return -1;
                }
            }
        }
        return minutes + seconds;
    }

    void schedule(std::string time, std::function<void()> func) {
        long long microseconds = time_mapper(time);
        if(-1 == microseconds) {
            std::cout << "Invalid time format." << std::endl;
            return;
        }
        std::thread t([microseconds, func](){
            while(true) {
                ::usleep(microseconds);
                func();
            }
        });
        t.detach();
    }
}