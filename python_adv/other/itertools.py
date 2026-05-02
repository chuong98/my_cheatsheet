"""
Comprehensive examples of Python itertools module.
Common patterns and use cases for efficient iteration.
"""

import itertools
from typing import Iterator


# ============================================================================
# 1. INFINITE ITERATORS
# ============================================================================

def count_example():
    """count(start, step) - infinite counter"""
    print("\n=== count() ===")
    # Start at 10, increment by 2, count forever, you can break manually
    counter = itertools.count(10, 2)
    for i, num in enumerate(counter):
        if i >= 5:
            break
        print(f"Count {i}: {num}")
    # Output: 10, 12, 14, 16, 18


def cycle_example():
    """cycle(iterable) - repeat elements indefinitely"""
    print("\n=== cycle() ===")
    colors = ['red', 'green', 'blue']
    cycler = itertools.cycle(colors)
    for i, color in enumerate(cycler):
        if i >= 7:
            break
        print(f"Position {i}: {color}")
    # Output: red, green, blue, red, green, blue, red


def repeat_example():
    """repeat(object, times) - repeat object n times"""
    print("\n=== repeat() ===")
    # Repeat 5 times
    for val in itertools.repeat("Hello", 5):
        print(val)
    
    # Useful with map
    result = list(map(pow, range(5), itertools.repeat(2)))
    print(f"Powers of 2: {result}")  # [0, 1, 4, 9, 16]


# ============================================================================
# 2. COMBINATORIC ITERATORS
# ============================================================================

def product_example():
    """product(*iterables, repeat) - Cartesian product"""
    print("\n=== product() ===")
    
    # Simple product
    colors = ['red', 'green']
    sizes = ['S', 'M', 'L']
    result = list(itertools.product(colors, sizes))
    print(f"Product: {result}")
    
    # With repeat
    coins = ['H', 'T']
    outcomes = list(itertools.product(coins, repeat=3))
    print(f"Coin flips (3 times): {outcomes}")
    print(f"Total outcomes: {len(outcomes)}")  # 2^3 = 8


def permutations_example():
    """permutations(iterable, r) - all ordered arrangements"""
    print("\n=== permutations() ===")
    
    letters = ['A', 'B', 'C']
    
    # All permutations of length 2
    perms = list(itertools.permutations(letters, 2))
    print(f"Permutations (r=2): {perms}")
    
    # All permutations (full length)
    all_perms = list(itertools.permutations(letters))
    print(f"All permutations: {all_perms}")
    print(f"Count: {len(all_perms)}")  # 3! = 6


def combinations_example():
    """combinations(iterable, r) - unordered selections without replacement"""
    print("\n=== combinations() ===")
    
    items = ['A', 'B', 'C', 'D']
    
    # Choose 2 items
    combs = list(itertools.combinations(items, 2))
    print(f"Combinations (r=2): {combs}")
    print(f"Count: {len(combs)}")  # C(4,2) = 6
    
    # Choose 3 items
    combs3 = list(itertools.combinations(items, 3))
    print(f"Combinations (r=3): {combs3}")


def combinations_with_replacement_example():
    """combinations_with_replacement(iterable, r) - with replacement"""
    print("\n=== combinations_with_replacement() ===")
    
    items = ['A', 'B', 'C']
    result = list(itertools.combinations_with_replacement(items, 2))
    print(f"Combinations with replacement: {result}")
    # Includes ('A', 'A'), ('B', 'B'), etc.


# ============================================================================
# 3. TERMINATING ITERATORS
# ============================================================================

def chain_example():
    """chain(*iterables) - concatenate iterables"""
    print("\n=== chain() ===")
    
    list1 = [1, 2, 3]
    list2 = ['a', 'b', 'c']
    list3 = [True, False]
    
    result = list(itertools.chain(list1, list2, list3))
    print(f"Chained: {result}")
    
    # chain.from_iterable - flatten nested iterables
    nested = [[1, 2], [3, 4], [5, 6]]
    flattened = list(itertools.chain.from_iterable(nested))
    print(f"Flattened: {flattened}")


def compress_example():
    """compress(data, selectors) - filter by boolean mask"""
    print("\n=== compress() ===")
    
    data = ['A', 'B', 'C', 'D', 'E']
    selectors = [1, 0, 1, 0, 1]  # True, False, True, False, True
    
    result = list(itertools.compress(data, selectors))
    print(f"Compressed: {result}")  # ['A', 'C', 'E']


def dropwhile_example():
    """dropwhile(predicate, iterable) - drop while predicate is true"""
    print("\n=== dropwhile() ===")
    
    data = [1, 3, 5, 8, 10, 12, 7, 9]
    
    # Drop while less than 8
    result = list(itertools.dropwhile(lambda x: x < 8, data))
    print(f"Drop while < 8: {result}")  # [8, 10, 12, 7, 9]


def takewhile_example():
    """takewhile(predicate, iterable) - take while predicate is true"""
    print("\n=== takewhile() ===")
    
    data = [1, 3, 5, 8, 10, 12, 7, 9]
    
    # Take while less than 8
    result = list(itertools.takewhile(lambda x: x < 8, data))
    print(f"Take while < 8: {result}")  # [1, 3, 5]


def filterfalse_example():
    """filterfalse(predicate, iterable) - opposite of filter()"""
    print("\n=== filterfalse() ===")
    
    data = [1, 2, 3, 4, 5, 6, 7, 8]
    
    # Get odd numbers (filter out even)
    odds = list(itertools.filterfalse(lambda x: x % 2 == 0, data))
    print(f"Odd numbers: {odds}")


def groupby_example():
    """groupby(iterable, key) - group consecutive elements"""
    print("\n=== groupby() ===")
    
    # Group consecutive elements
    data = ['A', 'A', 'B', 'B', 'B', 'C', 'A']
    for key, group in itertools.groupby(data):
        print(f"Key: {key}, Items: {list(group)}")
    
    # Group by length
    words = ['hi', 'bye', 'hello', 'world', 'foo']
    words.sort(key=len)  # Must sort first!
    print("\nGrouped by length:")
    for length, group in itertools.groupby(words, key=len):
        print(f"Length {length}: {list(group)}")


def islice_example():
    """islice(iterable, start, stop, step) - slice iterator"""
    print("\n=== islice() ===")
    
    data = range(20)
    
    # First 5 elements
    result = list(itertools.islice(data, 5))
    print(f"First 5: {result}")
    
    # Elements 5-10
    result = list(itertools.islice(data, 5, 10))
    print(f"Elements 5-10: {result}")
    
    # Every 3rd element
    result = list(itertools.islice(data, 0, 20, 3))
    print(f"Every 3rd: {result}")


def pairwise_example():
    """pairwise(iterable) - return consecutive pairs (Python 3.10+)"""
    print("\n=== pairwise() ===")
    
    data = [1, 2, 3, 4, 5]
    pairs = list(itertools.pairwise(data))
    print(f"Pairs: {pairs}")  # [(1,2), (2,3), (3,4), (4,5)]
    
    # Calculate differences
    diffs = [b - a for a, b in itertools.pairwise(data)]
    print(f"Differences: {diffs}")


def starmap_example():
    """starmap(function, iterable) - map with unpacked arguments"""
    print("\n=== starmap() ===")
    
    # Calculate powers
    data = [(2, 3), (3, 2), (10, 2)]
    result = list(itertools.starmap(pow, data))
    print(f"Powers: {result}")  # [8, 9, 100]
    
    # Calculate products
    data = [(2, 3), (4, 5), (6, 7)]
    result = list(itertools.starmap(lambda x, y: x * y, data))
    print(f"Products: {result}")


def tee_example():
    """tee(iterable, n) - split iterator into n independent iterators"""
    print("\n=== tee() ===")
    
    data = range(5)
    iter1, iter2 = itertools.tee(data, 2)
    
    print(f"Iterator 1: {list(iter1)}")
    print(f"Iterator 2: {list(iter2)}")


def zip_longest_example():
    """zip_longest(*iterables, fillvalue) - zip with padding"""
    print("\n=== zip_longest() ===")
    
    list1 = [1, 2, 3]
    list2 = ['a', 'b', 'c', 'd', 'e']
    
    # Regular zip stops at shortest
    result = list(zip(list1, list2))
    print(f"Regular zip: {result}")
    
    # zip_longest pads with None (or fillvalue)
    result = list(itertools.zip_longest(list1, list2, fillvalue=0))
    print(f"zip_longest: {result}")


# ============================================================================
# 4. PRACTICAL EXAMPLES
# ============================================================================

def sliding_window(iterable, n):
    """Create a sliding window of size n"""
    it = iter(iterable)
    window = tuple(itertools.islice(it, n))
    if len(window) == n:
        yield window
    for item in it:
        window = window[1:] + (item,)
        yield window


def sliding_window_example():
    """Practical: sliding window pattern"""
    print("\n=== Sliding Window ===")
    
    data = [1, 2, 3, 4, 5, 6, 7]
    windows = list(sliding_window(data, 3))
    print(f"Windows of size 3: {windows}")


def batching_example():
    """Batch data into fixed-size chunks"""
    print("\n=== Batching ===")
    
    data = range(10)
    batch_size = 3
    
    # Method 1: Using islice
    it = iter(data)
    batches = []
    while batch := list(itertools.islice(it, batch_size)):
        batches.append(batch)
    print(f"Batches: {batches}")


def flatten_nested_structure():
    """Flatten nested lists"""
    print("\n=== Flatten Nested ===")
    
    nested = [[1, 2, 3], [4, 5], [6, 7, 8, 9]]
    flattened = list(itertools.chain.from_iterable(nested))
    print(f"Flattened: {flattened}")


def unique_combinations_example():
    """Find all unique pairs/triplets"""
    print("\n=== Unique Combinations ===")
    
    # All unique pairs from a list
    items = ['apple', 'banana', 'cherry', 'date']
    pairs = list(itertools.combinations(items, 2))
    print(f"Unique pairs: {pairs}")


# ============================================================================
# MAIN EXECUTION
# ============================================================================

if __name__ == "__main__":
    print("=" * 70)
    print("PYTHON ITERTOOLS EXAMPLES")
    print("=" * 70)
    
    # Infinite iterators
    count_example()
    cycle_example()
    repeat_example()
    
    # Combinatoric iterators
    product_example()
    permutations_example()
    combinations_example()
    combinations_with_replacement_example()
    
    # Terminating iterators
    chain_example()
    compress_example()
    dropwhile_example()
    takewhile_example()
    filterfalse_example()
    groupby_example()
    islice_example()
    pairwise_example()
    starmap_example()
    tee_example()
    zip_longest_example()
    
    # Practical examples
    sliding_window_example()
    batching_example()
    flatten_nested_structure()
    unique_combinations_example()
    
    print("\n" + "=" * 70)
    print("Examples completed!")
    print("=" * 70)
