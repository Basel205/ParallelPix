#include "system_info.h"
#include <windows.h>
#include <string>

std::string get_cpu_info() {
    char buffer[128];
    DWORD buffer_size = sizeof(buffer);
    if (RegGetValueA(HKEY_LOCAL_MACHINE,
                     "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                     "ProcessorNameString",
                     RRF_RT_REG_SZ,
                     nullptr,
                     buffer,
                     &buffer_size) == ERROR_SUCCESS) {
        return std::string(buffer);
    }
    return "Unknown CPU";  // Added missing closing brace
}

int get_core_count() {
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    return sys_info.dwNumberOfProcessors;
}
