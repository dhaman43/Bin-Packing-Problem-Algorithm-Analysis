#include <vector>
#include <chrono>
#include "metrics.h"

static const int CAP = 100;

Result bestFit(std::vector<int> items) {
    auto start = std::chrono::high_resolution_clock::now();
    long long mem_before = getMemoryUsageKB();

    std::vector<int> bins;

    for (int x : items) {
        int best = -1, minSpace = 1e9;

        for (int i = 0; i < bins.size(); i++) {
            if (bins[i] + x <= CAP) {
                int space = CAP - (bins[i] + x);
                if (space < minSpace) {
                    minSpace = space;
                    best = i;
                }
            }
        }

        if (best == -1) bins.push_back(x);
        else bins[best] += x;
    }

    auto end = std::chrono::high_resolution_clock::now();
    long long mem_after = getMemoryUsageKB();

    return {
        (int)bins.size(),
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
        mem_after - mem_before,
        0.0
    };
}
