#include "logger.h"
#include <iostream>
#include <fstream>

std::ofstream log_file;

void init_logger(const std::string& filename) {
    log_file.open(filename, std::ios::out | std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

void log(const std::string& message) {
    if (log_file.is_open()) {
        log_file << message << std::endl;
    } else {
        std::cerr << "Log file not initialized!" << std::endl;
    }
}

void close_logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}
