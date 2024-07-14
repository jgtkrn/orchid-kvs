#include <cron/cron.hh>

namespace cron {
    long long time_mapper(std::string time) {
        long long mapped_time = 0;

        long long d_t = 86400000000;
        long long h_t = 3600000000;  
        long long m_t = 60000000;     
        long long s_t = 1000000;
        long long ms_t = 1000;

        std::string temp_time_string = "";
        for (unsigned long i = 0; i < time.size(); ++i) {
            if (isdigit(time[i])) {
                temp_time_string += time[i];
            } else {
                if (time[i] == 'D' || time[i] == 'd') {
                    mapped_time += std::stoull(temp_time_string) * d_t;
                    temp_time_string = "";
                } else if (time[i] == 'H' || time[i] == 'h') {
                    mapped_time += std::stoull(temp_time_string) * h_t;
                    temp_time_string = "";
                } else if (time[i] == 'M' || time[i] == 'm') {
                    if (i + 1 < time.size() && (time[i + 1] == 'S' || time[i + 1] == 's')) {
                        mapped_time += std::stoull(temp_time_string) * ms_t;
                        temp_time_string = "";
                        i++;
                    } else {
                        mapped_time += std::stoull(temp_time_string) * m_t;
                        temp_time_string = "";
                    }
                } else if (time[i] == 'S' || time[i] == 's') {
                    mapped_time += std::stoull(temp_time_string) * s_t;
                    temp_time_string = "";
                } else if (time[i] == 'U' || time[i] == 'u') {
                    if (i + 1 < time.size() && (time[i + 1] == 'S' || time[i + 1] == 's')) {
                        mapped_time += std::stoull(temp_time_string);
                        temp_time_string = "";
                        i++;
                    }
                } else {
                    return -1;
                }
            }
        }
        return mapped_time;
    }

    void schedule(std::string time, std::function<void()> func) {
        long long microseconds = time_mapper(time);
        if(-1 == microseconds) {
            std::cout << "Invalid time format." << std::endl;
            return;
        }
        std::thread t([microseconds, func](){
            while(true) {
                ::sleep(microseconds);
                func();
            }
        });
        t.detach();
    }
}