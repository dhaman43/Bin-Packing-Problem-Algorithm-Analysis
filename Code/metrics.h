#pragma once
#include <vector>
#include <chrono>

struct Result {
    int bins;
    long long runtime_ms;
    long long memory_bytes;
    double approximation_ratio; // only used when applicable
};

long long getMemoryUsageKB();
