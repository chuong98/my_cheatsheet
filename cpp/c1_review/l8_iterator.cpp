#include <iostream>
#include <string>

int main() {
    //array iterator
    int arr[] = {10, 20, 30, 40, 50};
    for (auto it = std::begin(arr); it != std::end(arr); ++it) {
        int index = it - std::begin(arr);
        std::cout << "Element at index " << index << ": " << *it << std::endl;
    }
    std::cout << std::endl;

    //vector iterator
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        int index = it - vec.begin();
        std::cout << "Element at index " << index << ": " << *it << std::endl;
    }

    //  constant iterator: // Using cbegin and cend for constant access for read-only
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        int index = it - vec.cbegin();
        std::cout << "Constant element at index " << index << ": " << *it << std::endl;
        // try to change the value (will not compile)
        // *it = 100; // Uncommenting this line will cause a compilation error
    }

    //reverse iterator
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        int index = it - vec.rbegin();
        std::cout << "Reverse element at index " << index << ": " << *it << std::endl;
    }

    //string iterator is the same as vector iterator
    std::string str = "Hello";
    for (auto it = str.begin(); it != str.end(); ++it) {
        int index = it - str.begin();
        std::cout << "Character at index " << index << ": " << *it << std::endl;
    }
    std::cout << std::endl;

    /*  summary of iterators
        - Array iterator: Uses pointers to iterate over array elements.
        - Vector iterator: Similar to array iterator, but provides additional functionality (e.g., bounds checking).
        - Constant iterator: Read-only access to elements, preventing modification.
        - Reverse iterator: Iterates over elements in reverse order.
        - String iterator: Same as vector iterator, but for string elements.
    */

    return 0;
}