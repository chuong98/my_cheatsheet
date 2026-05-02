#include <iostream>
#include <algorithm>

#include <vector>
#include <numeric>
#include <iterator>


/*
 algorithm library provides a collection of functions to perform operations on sequences (like arrays, vectors, etc.)
 - looping: `std::for_each`, `std::for_each_n`
 - Sorting: `std::sort`
 - Searching: `std::find`, `std::binary_search`
 - Min/Max: `std::min_element`, `std::max_element`
 - Counting: `std::count`
 - Transforming: `std::transform`
 - Accumulating: `std::accumulate`
 it takes iterators of begin and end of the sequence, and applies the operation to each element in that range.
 It can be used with any container that supports iterators, such as arrays, vectors, lists, etc.
 list of algo functions: https://en.cppreference.com/w/cpp/algorithm
*/

int main() {
    //--------------------------------------------

    std::cout << std::endl;
    // Example with array
    int arr[] = {10, 4, 7, 2, 6};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Original array: ";
    std::for_each_n(std::begin(arr), 5, [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
    
    // Sort the array
    std::sort(arr, arr + arr_size);
    std::cout << "Sorted array: ";
    for (int i = 0; i < arr_size; i++) std::cout << arr[i] << " ";
    std::cout << std::endl;
    
    // Find element in array
    int* found = std::find(arr, arr + arr_size, 7);
    if (found != arr + arr_size) {
        std::cout << "Found 7 in array at position: " << std::distance(arr, found) << std::endl;
    }
    std::cout << std::endl;
    
    //--------------------------------------------
    std::vector<int> nums = {5, 2, 8, 1, 9, 3};
    std::cout << "Original vector: ";
    std::for_each(nums.begin(), nums.end(), [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;
    // Sort the vector
    std::sort(nums.begin(), nums.end());
    std::cout << "Sorted vector: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Find an element
    auto it = std::find(nums.begin(), nums.end(), 8);
    if (it != nums.end()) {
        std::cout << "Found 8 at position: " << std::distance(nums.begin(), it) << std::endl;
    }
    
    // Find min and max elements
    auto min_it = std::min_element(nums.begin(), nums.end());
    auto max_it = std::max_element(nums.begin(), nums.end());
    std::cout << "Min: " << *min_it << ", Max: " << *max_it << std::endl;
    
    // Count occurrences
    int count = std::count(nums.begin(), nums.end(), 2);
    std::cout << "Count of 2: " << count << std::endl;
    
    // Accumulate (sum all elements)
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum: " << sum << std::endl;

    // Transform elements (square each number)
    std::vector<int> squared(nums.size());
    std::transform(nums.begin(), nums.end(), squared.begin(), [](int x) { return x * x; });
    
    std::cout << "Squared: ";
    for (int n : squared) std::cout << n << " ";
    std::cout << std::endl;
    
    return 0;
}