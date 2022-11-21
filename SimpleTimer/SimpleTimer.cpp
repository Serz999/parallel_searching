#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(const std::string &out_filename) {
    this->out_filename = out_filename;
}

void SimpleTimer::Start() {
    begin = std::chrono::high_resolution_clock::now();
}

void SimpleTimer::Stop(const std::string &key) {
    end = std::chrono::high_resolution_clock::now();
    duration = end - begin;
    std::cout << duration.count() << std::endl;
    std::ofstream ofs(out_filename ,std::ofstream::app);;
    if (!ofs.is_open()) {
        std::cout << "ERROR: incorrect name will be assign" << std::endl;
    } else {
        ofs << key << " : " << duration.count() << " ms" << std::endl;
        ofs.close();
    }
}
