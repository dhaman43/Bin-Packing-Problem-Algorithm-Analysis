import random

def generate_dataset(n, capacity, seed=42):
    random.seed(seed)
    return [random.randint(1, 50) for _ in range(n)]

def hard_dataset(n, capacity):
    return [capacity//2 + 1 for _ in range(n)]
