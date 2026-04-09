#include <vector>
#include <chrono>
#include "metrics.h"

static const int CAP = 100;

Result worstFit(std::vector<int> items) {
    auto start = std::chrono::high_resolution_clock::now();
    long long mem_before = getMemoryUsageKB();

    std::vector<int> bins;

    for (int x : items) {
        int worst = -1, maxSpace = -1;

        for (int i = 0; i < bins.size(); i++) {
            if (bins[i] + x <= CAP) {
                int space = CAP - (bins[i] + x);
                if (space > maxSpace) {
                    maxSpace = space;
                    worst = i;
                }
            }
        }

        if (worst == -1) bins.push_back(x);
        else bins[worst] += x;
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
