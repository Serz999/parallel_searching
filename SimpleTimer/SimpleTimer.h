#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>

class SimpleTimer {
public:
    SimpleTimer(const std::string &out_filename);

    void Start();

    void Stop(const std::string &key);

    ~SimpleTimer() {};
private:
    std::string out_filename;
    std::chrono::time_point<std::chrono::high_resolution_clock> begin;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double, std::milli> duration;
};