#include <iostream>
#include <vector>
#include <string>

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    //------------------------------------------------
    // This program demonstrates different types of arrays in C++:
    //------------------------------------------------
    //1. Array
    //------------------------------------------------
    // Array: an indexed block of contiguous memory
    // - It has a fixed size and cannot be resized. TThe size must be known at compile time.
    // - Elements are accessed using indices, starting from 0.
    // - It can't be copied or assigned directly, but can be passed to functions.
    // - No direct way to find number of elements in an array.
    // - It can be passed to functions by reference or by pointer.
    
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Array elements: ";
    printArray(arr, 5);
    // Using a pointer to access array elements
    int *ptr = arr;
    std::cout << "Array elements using pointer: ";
    for (int i = 0; i < 5; i++) {
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;

    // Using a reference to access array elements
    int &ref = arr[0];
    std::cout << "First element using reference: " << ref << std::endl;

    // get the size of the array using sizeof
    std::cout << "Size of array: " << sizeof(arr) / sizeof(arr[0]) << std::endl;

    //------------------------------------------------
    //2. Dynamic Array
    //------------------------------------------------
    // Using a dynamic array : if we don't know the size at compile time, but at runtime
    // - If we want to change the size of the array, we need to allocate a new array and copy the elements.
    // - Must be explicitly deleted to avoid memory leaks.
    // - Can be created using new and deleted using delete.
    // - Undefined behavior if accessed out of bounds.( use after deleted or deleted twice)
    int *dynamicArr = new int[5]{6, 7, 8, 9, 10};

    // changing the size of the dynamic array
    int newSize = 10;
    int *tempArr = new int[newSize];
    for (int i = 0; i < 5; i++) {
        tempArr[i] = dynamicArr[i]; // Copying old elements
    }
    delete[] dynamicArr; // Free old memory
    dynamicArr = tempArr; // Point to new array
    std::cout << "Dynamic array elements: ";
    printArray(dynamicArr, newSize);

    //------------------------------------------------
    //3. Using a vector
    //------------------------------------------------
    // Vector: a dynamic array that can grow and shrink in size
    // - It can be resized, and elements can be added or removed.
    // - correctly handles copying and assignment by allocating a new block
    // - It manages memory automatically, so no need to delete it explicitly.
    // - It can be passed to functions by reference or by pointer.
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Vector elements: ";
    // accessing vector elements using range-based for loop
    for (const auto &element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Using vector's data() method to get pointer to array
    vec.pop_back(); // Deleting the last element
    vec.push_back(6); // Adding an element to the vector
    vec[2] = 10; // Modifying an element in the vector
    vec.erase(vec.begin() + 1); // delete element at index 1
    std::cout << "Modified vector elements: ";
    printArray(vec.data(), vec.size());

    

    //------------------------------------------------
    // 4.Strings
    // string is a subclass of vector<char>
    std::string hello = "Hello, World!";
    std::cout << "String: " << hello << std::endl;
    std::cout << "String length: " << hello.length() << std::endl;
    std::cout << "String size: " << hello.size() << std::endl; // size() and length() are equivalent for strings
    std::cout << "First character: " << hello[0] << std::endl;
    std::cout << "Last character: " << hello[hello.length() - 1] << std::endl;
    //concatenation
    hello += " How are you?";
    std::cout << "Concatenated string: " << hello << std::endl;
    // substring
    std::string sub = hello.substr(0, 5); // Get first 5 characters
    std::cout << "Substring: " << sub << std::endl;
    // find a character
    size_t pos = hello.find("World"); // Find position of "World"
    if (pos != std::string::npos) {
        std::cout << "'World' found at position: " << pos << std::endl;
    } else {
        std::cout << "'World' not found" << std::endl;
    }
    return 0;
    //------------------------------------------------
    // 4. Summary
    // when should we use each type?
    // - Use arrays when the size is fixed and known at compile time.
    // - Use dynamic arrays when the size is not known at compile time, but you need to manage memory manually.
    // - Use vectors when you need a dynamic array that can grow and shrink in size, with automatic memory management.
    //------------------------------------------------
    //Why not use Vector all the time?
    // - Vectors have some overhead due to dynamic memory management and resizing.
    // - If performance is critical and the size is known, arrays can be more efficient.
    // - Vectors are more flexible and easier to use, but arrays can be more performant in some cases.
    //------------------------------------------------
    // when use length or size?
    // - Use length() for strings to get the number of characters.
    // - Use size() for vectors to get the number of elements.
    // - Use sizeof for arrays to get the size in bytes, and then divide by the size of an element to get the number of elements.
    // - Use data() for vectors to get a pointer to the underlying array.
}