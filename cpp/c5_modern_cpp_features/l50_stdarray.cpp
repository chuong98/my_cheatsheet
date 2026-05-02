#include <iostream>
#include <array>
#include <algorithm>
/* 
- c++ has a built-in array inherited from C. It is faster than std::vector but has serious limitations: 
    + fixed size, no simple way to find size, silent conversion to pointer,
    + no bounds checking,
    + no STL algorithm compatibility.
    + array cannot be assigned to each other
- modern C++ provides std::array, which has similar interface to STL containers, while retaining speed of built-in array:
    + fixed size, but size is known at compile time and can be queried using .size() method.
    + bounds checking using .at() method.
    + STL algorithm compatibility, can be used with algorithms like std::sort, std::find, etc.
    + can be assigned to each other
    + supports iterators, front(), back(), empty(), at(), data() methods as in vector.
- std::array is a safer and more flexible alternative to built-in arrays in modern C++.
- std::array is a template class that takes the type of elements and the size as template parameters.
- std::array is part of the C++ Standard Library and is defined in the <array> header file.
 */
int main() {
    // Regular C-style array
    int regular_array[5] = {1, 2, 3, 4, 5};
    
    // std::array
    std::array<int, 5> std_array = {1, 2, 3, 4, 5};
    
    std::cout << "=== Regular Array vs std::array ===\n\n";
    
    // 1. Size information
    std::cout << "1. Size information:\n";
    // Regular array loses size info when passed to functions
    std::cout << "Regular array size (using sizeof): " << sizeof(regular_array)/sizeof(regular_array[0]) << "\n";
    std::cout << "std::array size: " << std_array.size() << "\n\n";
    
    // 2. Bounds checking (at() method)
    std::cout << "2. Bounds checking:\n";
    try {
        std::cout << "std::array.at(10): ";
        std::cout << std_array.at(10) << "\n"; // Throws exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    std::cout << "Regular array[10]: " << regular_array[10] << " (undefined behavior)\n\n";
    
    // 3. STL algorithm compatibility
    std::cout << "3. STL algorithm compatibility:\n";
    std::cout << "Before sorting:\n";
    std::cout << "std::array: ";
    for (const auto& elem : std_array) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    
    // Sort std::array using STL algorithm
    std::sort(std_array.rbegin(), std_array.rend()); // Reverse sort
    
    std::cout << "After reverse sorting std::array: ";
    for (const auto& elem : std_array) {
        std::cout << elem << " ";
    }
    std::cout << "\n\n";
    
    // 4. Assignment and comparison
    std::cout << "4. Assignment and comparison:\n";
    std::array<int, 5> another_array = {5, 4, 3, 2, 1};
    std::array<int, 5> copy_array;
    
    copy_array = another_array; // Direct assignment works
    std::cout << "Assignment works with std::array\n";
    
    if (another_array == copy_array) {
        std::cout << "Comparison works with std::array\n";
    }
    
    // Regular arrays cannot be assigned or compared directly
    // int another_regular[5] = {5, 4, 3, 2, 1};
    // regular_array = another_regular; // Compilation error
    
    // 5. Iterators
    std::cout << "\n5. Iterator support:\n";
    std::cout << "Using iterators with std::array: ";
    for (auto it = std_array.begin(); it != std_array.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 6. Front and back access
    std::cout << "\n6. Front and back access:\n";
    std::cout << "First element: " << std_array.front() << "\n";
    std::cout << "Last element: " << std_array.back() << "\n";
    
    // 7. Empty check
    std::cout << "\n7. Empty check:\n";
    std::cout << "Is std::array empty? " << (std_array.empty() ? "Yes" : "No") << "\n";
    
    return 0;
}