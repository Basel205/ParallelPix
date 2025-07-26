// // cpu_monitor.cpp
// #include "cpu_monitor.h"
// #include <windows.h>

// double get_cpu_usage() {
//     FILETIME idle_time, kernel_time, user_time;
//     if (GetSystemTimes(&idle_time, &kernel_time, &user_time)) {
//         static ULARGE_INTEGER last_idle = {{0}}, last_kernel = {{0}}, last_user = {{0}};
//         ULARGE_INTEGER idle, kernel, user;
        
//         idle.LowPart = idle_time.dwLowDateTime;
//         idle.HighPart = idle_time.dwHighDateTime;
        
//         kernel.LowPart = kernel_time.dwLowDateTime;
//         kernel.HighPart = kernel_time.dwHighDateTime;
        
//         user.LowPart = user_time.dwLowDateTime;
//         user.HighPart = user_time.dwHighDateTime;

//         ULONGLONG sys = ((kernel.QuadPart - last_kernel.QuadPart) +
//                         (user.QuadPart - last_user.QuadPart));
//         ULONGLONG idle_diff = idle.QuadPart - last_idle.QuadPart;

//         last_idle = idle;
//         last_kernel = kernel;
//         last_user = user;

//         if (sys == 0) return 0.0;
        
//         return (1.0 - (double)idle_diff / sys) * 100.0;
//     }
//     return -1.0;  // Added missing closing brace
// }


#include "cpu_monitor.h"
#include <windows.h>
#include <chrono>

// Process-specific CPU time measurement
static ULARGE_INTEGER last_cpu_time;
static std::chrono::steady_clock::time_point last_time;

double get_cpu_usage() {
    FILETIME creation, exit, kernel, user;
    
    // Get current process times
    if (!GetProcessTimes(GetCurrentProcess(), &creation, &exit, &kernel, &user))
        return -1.0;

    // Calculate current CPU time
    ULARGE_INTEGER current_cpu;
    current_cpu.LowPart = user.dwLowDateTime + kernel.dwLowDateTime;
    current_cpu.HighPart = user.dwHighDateTime + kernel.dwHighDateTime;

    // Calculate elapsed wall-clock time
    auto now = std::chrono::steady_clock::now();
    double elapsed_sec = std::chrono::duration<double>(now - last_time).count();
    last_time = now;

    // Calculate CPU time delta
    double cpu_delta = (current_cpu.QuadPart - last_cpu_time.QuadPart) / 10000000.0;
    last_cpu_time = current_cpu;

    // Prevent division by zero
    if (elapsed_sec < 0.001) return 0.0;
    
    // Return percentage of total CPU capacity (100% per core)
    return (cpu_delta / elapsed_sec) * 100.0;
}
