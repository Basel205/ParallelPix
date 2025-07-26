#pragma once
#include <chrono>

class Timer {
private:
    bool running;
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    Timer();
    void start();
    double stop();
};
