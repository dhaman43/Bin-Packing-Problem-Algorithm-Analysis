best_solution = float('inf')

def branch_and_bound(items, capacity, bins):
    global best_solution

    if len(bins) >= best_solution:
        return

    if not items:
        best_solution = min(best_solution, len(bins))
        return

    item = items[0]
    rest = items[1:]

    for i in range(len(bins)):
        if sum(bins[i]) + item <= capacity:
            bins[i].append(item)
            branch_and_bound(rest, capacity, bins)
            bins[i].pop()

    bins.append([item])
    branch_and_bound(rest, capacity, bins)
    bins.pop()

def solve_branch_and_bound(items, capacity):
    global best_solution
    best_solution = float('inf')
    branch_and_bound(items, capacity, [])
    return best_solution
