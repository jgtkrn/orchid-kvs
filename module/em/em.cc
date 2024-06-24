#include<em/em.h>
namespace em {
    void err_msg(std::string msg) {
        // append log file
        std::cout << msg << std::endl;
    }
}