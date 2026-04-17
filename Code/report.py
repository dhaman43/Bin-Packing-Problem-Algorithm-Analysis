import os.path
import time
import tracemalloc
import csv

from datasets import generate_dataset
from first_fit import first_fit
from best_fit import best_fit
from worst_fit import worst_fit
from branch_bound import solve_branch_and_bound
from aco import aco_bin_packing

CAPACITY = 100

def measure(func, items):
    tracemalloc.start()
    start = time.perf_counter()

    result = func(items, CAPACITY)

    end = time.perf_counter()
    current, peak = tracemalloc.get_traced_memory()
    tracemalloc.stop()

    if isinstance(result, list):
        bins_used = len(result)
    else:
        bins_used = result
    execution_time = (end - start) * 1000
    return bins_used, execution_time, peak / 1024

def main():
    sizes = [20, 50, 100, 200, 500, 1000]

    with open("results/results.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["n", "Algorithm", "Bins Used", "Time (s)", "Memory (KB)"])

        for n in sizes:
            items = generate_dataset(n, CAPACITY)

            for name, algo in [
                ("First Fit", first_fit),
                ("Best Fit", best_fit),
                ("Worst Fit", worst_fit),
                ("ACO", lambda items, cap: aco_bin_packing(items, cap)),
            ]:
                bins_used, t, mem = measure(algo, items)
                writer.writerow([n, name, bins_used, t, mem])

            if n <= 20:
                bins_used, t, mem = measure(
                    lambda items, cap: solve_branch_and_bound(items, cap),
                    items
                )
                writer.writerow([n, "Branch & Bound", bins_used, t, mem])

if __name__ == "__main__":
    main()
