#include "effects.hpp"
#include "../utils/timer.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>  // For debug output

namespace fs = std::filesystem;

void generate_test_image(ImageProcessor& proc, int size) {
    proc.width = size;
    proc.height = size;
    proc.pixels.resize(size * size);
    for(int i = 0; i < size*size; i++) {
        proc.pixels[i] = {
            static_cast<unsigned char>(rand()%256),
            static_cast<unsigned char>(rand()%256),
            static_cast<unsigned char>(rand()%256)
        };
    }
}

void run_benchmarks() {
    const std::vector<std::string> filters = {"blur", "anime", "oil", "pencil", "thermal"};
    const std::string log_dir = "../../benchmarking/performance_logs";  // Adjusted path
    
    try {
        if (!fs::exists(log_dir)) {
            fs::create_directories(log_dir);
            std::cout << "Created directory: " << log_dir << std::endl;
        }

        std::ofstream csv(log_dir + "/results.csv");
        if (!csv.is_open()) {
            std::cerr << "Failed to open CSV file for writing!" << std::endl;
            return;
        }

        csv << "Filter,ImageSize,SerialTime,ParallelTime\n";
        std::cout << "Starting benchmarks..." << std::endl;

        for (const auto& filter : filters) {
            for (int size : {512, 1024, 2048}) {
                std::cout << "Testing " << filter << " at size " << size << std::endl;
                
                ImageProcessor proc;
                generate_test_image(proc, size);

                // Serial execution
                Timer t;
                t.start();
                proc.apply_filter(filter, 3, false);
                double serial_time = t.stop();

                // Parallel execution
                t.start();
                proc.apply_filter(filter, 3, true);
                double parallel_time = t.stop();

                csv << filter << "," << size << "," 
                    << serial_time << "," << parallel_time << "\n";
            }
        }
        std::cout << "Benchmarks completed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Benchmark error: " << e.what() << std::endl;
    }
}








// #include "effects.hpp"
// #include "../utils/timer.h"
// #include "../utils/logger.h"
// #include "../utils/system_info.h"
// #include <filesystem>
// #include <fstream>
// #include <vector>
// #include <iostream>

// namespace fs = std::filesystem;

// void generate_test_image(ImageProcessor& proc, int size) {
//     proc.width = size;
//     proc.height = size;
//     proc.pixels.resize(size * size);
//     for(int i = 0; i < size*size; i++) {
//         proc.pixels[i] = {
//             static_cast<unsigned char>(rand()%256),
//             static_cast<unsigned char>(rand()%256),
//             static_cast<unsigned char>(rand()%256)
//         };
//     }
// }

// void run_benchmarks() {
//     init_logger("benchmark.log");
//     log("=== Starting Benchmarks ===");
    
//     const std::vector<std::string> filters = {"blur", "anime", "oil", "pencil", "thermal"};
//     const std::string log_dir = "../../benchmarking/performance_logs";
    
//     try {
//         fs::create_directories(log_dir);
//         std::ofstream csv(log_dir + "/results.csv");
        
//         csv << "Filter,ImageSize,SerialTime,ParallelTime\n";
//         log("System Specifications:");
//         log("CPU: " + get_cpu_info());
//         log("Cores: " + std::to_string(get_core_count()));

//         for (const auto& filter : filters) {
//             for (int size : {512, 1024, 2048}) {
//                 ImageProcessor proc;
//                 generate_test_image(proc, size);

//                 // Serial execution
//                 Timer serial_timer;
//                 serial_timer.start();
//                 proc.apply_filter(filter, 3, false);
//                 double serial_time = serial_timer.stop();

//                 // Parallel execution
//                 Timer parallel_timer;
//                 parallel_timer.start();
//                 proc.apply_filter(filter, 3, true);
//                 double parallel_time = parallel_timer.stop();

//                 csv << filter << "," << size << "," 
//                     << serial_time << "," << parallel_time << "\n";
//             }
//         }
//         log("Benchmarks completed successfully!");
//     } catch (const std::exception& e) {
//         log("Benchmark error: " + std::string(e.what()));
//     }
//     close_logger();
// }
