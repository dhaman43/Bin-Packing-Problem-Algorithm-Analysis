#include "metrics.h"
#include <unistd.h>
#include <fstream>

long long getMemoryUsageKB() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (getline(file, line)) {
        if (line.find("VmRSS:") == 0) {
            long long kb = 0;
            sscanf(line.c_str(), "VmRSS: %lld", &kb);
            return kb * 1024; // convert KB → bytes
        }
    }
    return 0;
}
