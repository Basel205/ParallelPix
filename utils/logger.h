// logger.h
#pragma once
#include <string>

void init_logger(const std::string& filename);
void log(const std::string& message);
void close_logger();
