#include <iostream>
#include <vector>
#include <array>

int main() {
    // Array examples
    int arr[] = {1, 2, 3, 4, 5};
    std::array<int, 5> std_arr = {10, 20, 30, 40, 50};
    
    // Vector example
    std::vector<int> vec = {100, 200, 300, 400, 500};
    
    std::cout << "=== ARRAY ITERATIONS ===\n";
    
    // 1. Traditional for loop with array
    std::cout << "Traditional for loop (C-style array): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    // 2. Range-based for loop (C++11/17)
    std::cout << "Range-based for loop (C-style array): ";
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << "\n";
    
    // 3. Range-based for loop with std::array
    std::cout << "Range-based for loop (std::array): ";
    for (const auto& element : std_arr) {
        std::cout << element << " ";
    }
    std::cout << "\n";
    
    // 4. Iterator-based loop with std::array
    std::cout << "Iterator-based loop (std::array): ";
    for (auto it = std_arr.begin(); it != std_arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    std::cout << "\n=== VECTOR ITERATIONS ===\n";
    
    // 5. Traditional for loop with vector
    std::cout << "Traditional for loop (vector): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
    
    // 6. Range-based for loop with vector
    std::cout << "Range-based for loop (vector): ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";
    
    // 7. Iterator-based loop with vector
    std::cout << "Iterator-based loop (vector): ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 8. C++17 structured bindings with enumerate-like approach
    std::cout << "Range-based with index (C++17 style): ";
    for (const auto& [index, value] : std::vector<std::pair<size_t, int>>{
        {0, vec[0]}, {1, vec[1]}, {2, vec[2]}, {3, vec[3]}, {4, vec[4]}}) {
        std::cout << "[" << index << "]=" << value << " ";
    }
    std::cout << "\n";
    
    // 9. Algorithm-based iteration (C++17)
    std::cout << "std::for_each (vector): ";
    std::for_each(vec.begin(), vec.end(), [](const int& element) {
        std::cout << element << " ";
    });
    std::cout << "\n";
    

    // when we want to iterate and remove and modify elements, we need to use traditional for loop or use std::remove_if
    std::cout << "Removing elements greater than 300 from vector: ";
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int value) {
        return value > 300;
    }), vec.end());
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    // or traditional for loop
    std::cout << "Removing elements greater than 300 from vector (traditional for loop): ";
    for (size_t i = 0; i < vec.size();) {
        if (vec[i] > 300) {
            vec.erase(vec.begin() + i);
        } else {
            ++i;
        }
    }
    return 0;
}