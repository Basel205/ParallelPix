#include "timer.h"
#include <chrono>

Timer::Timer() : running(false), start_time(), end_time() {}

void Timer::start() {
    running = true;
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::stop() {
    if (!running) return 0.0;
    end_time = std::chrono::high_resolution_clock::now();
    running = false;
    return std::chrono::duration<double>(end_time - start_time).count();
}
