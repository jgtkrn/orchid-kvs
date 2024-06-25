#include<em/em.hh>
namespace em {
    void err_msg(std::string msg) {
        // append log file
        std::cout << msg << std::endl;
    }

    void norm_msg(std::string msg) {
        std::cout << msg << std::endl;
    }
}
