#include "effects.hpp"
#include "utils/timer.h"
#include "benchmarking/benchmark.h"
#include "libs/stb/stb_image.h"
#include "libs/stb/stb_image_write.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc > 1 && std::string(argv[1]) == "--benchmark") {
        run_benchmarks();
        return 0;
    }

    if(argc < 4) {
        std::cout << "Usage: " << argv[0] << " <input> <output> <filter> [radius] [--parallel]\n";
        return 1;
    }

    bool parallel = false;
    int param = 3;
    
    // Parse command line
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "--parallel") {
            parallel = true;
            // Remove from arguments
            for(int j = i; j < argc-1; ++j)
                argv[j] = argv[j+1];
            argc--;
            break;
        }
    }

    if(argc > 4 && std::isdigit(argv[4][0])) {
        param = std::max(1, std::stoi(argv[4]));
    }

    ImageProcessor processor;
    if(!processor.load(argv[1])) {
        std::cerr << "Error loading image!\n";
        return 1;
    }

    #ifdef _OPENMP
    if(parallel) {
        omp_set_num_threads(omp_get_max_threads());
        std::cout << "Using " << omp_get_max_threads() << " threads\n";
    }
    #endif

    Timer timer;
    timer.start();
    processor.apply_filter(argv[3], param, parallel);
    double elapsed = timer.stop();

    if(!processor.save(argv[2])) {
        std::cerr << "Error saving image!\n";
        return 1;
    }

    std::cout << "Completed in " << elapsed << "s (" 
              << (parallel ? "parallel" : "serial") << " mode)\n";
    return 0;
}




// #include "effects.hpp"
// #include "utils/timer.h"
// #include "utils/logger.h"
// #include "benchmarking/benchmark.h"
// #include <iostream>

// int main(int argc, char* argv[]) {
//     init_logger("app.log");
    
//     if(argc > 1 && std::string(argv[1]) == "--benchmark") {
//         run_benchmarks();
//         close_logger();
//         return 0;
//     }

//     if(argc < 4) {
//         std::cout << "Usage: " << argv[0] << " <input> <output> <filter> [radius] [--parallel]\n";
//         close_logger();
//         return 1;
//     }

//     bool parallel = false;
//     int param = 3;
    
//     // Parse --parallel flag
//     for(int i = 1; i < argc; ++i) {
//         if(std::string(argv[i]) == "--parallel") {
//             parallel = true;
//             break;
//         }
//     }

//     ImageProcessor processor;
//     if(!processor.load(argv[1])) {
//         std::cerr << "Error loading image!\n";
//         close_logger();
//         return 1;
//     }

//     #ifdef _OPENMP
//     if(parallel) {
//         omp_set_num_threads(omp_get_max_threads());
//         std::cout << "Using " << omp_get_max_threads() << " threads\n";
//     }
//     #endif

//     Timer timer;
//     timer.start();
//     processor.apply_filter(argv[3], param, parallel);
//     double elapsed = timer.stop();

//     if(!processor.save(argv[2])) {
//         std::cerr << "Error saving image!\n";
//         close_logger();
//         return 1;
//     }

//     std::cout << "Completed in " << elapsed << "s (" 
//               << (parallel ? "parallel" : "serial") << " mode)\n";
//     close_logger();
//     return 0;
// }
