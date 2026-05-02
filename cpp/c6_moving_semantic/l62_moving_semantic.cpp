
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class DataContainer {
private:
    std::vector<int> data;
    std::string name;

public:
    // Constructor
    DataContainer(const std::string& n, std::vector<int> d) 
        : name(n), data(std::move(d)) {
        std::cout << "DataContainer created with " << data.size() << " elements\n";
    }
    
    // Move constructor
    DataContainer(DataContainer&& other) noexcept 
        : name(std::move(other.name)), data(std::move(other.data)) {
        std::cout << "DataContainer moved\n";
    }
    
    void print() const {
        std::cout << "Name: " << name << ", Data size: " << data.size() << std::endl;
    }
};

// Function that takes data by move
void processData(DataContainer container) {
    std::cout << "Processing data:\n";
    container.print();
}

// ✅ Use reference/pointer for inspection/reading/ or direct modifying, 
// and the variable will be updated and continue to use in the main scope.
/* Use Reference (const T&) when:
- You want to read/inspect the data without taking ownership
- The original object should remain unchanged
- You want to avoid copying but keep the original */
void analyzeData(const std::vector<int>& data) {
    std::cout << "Data size: " << data.size() << std::endl;
    // Original vector remains intact
}


// Function that takes vector by move
/* Use Move (T&& or std::move()) when:
- You want to transfer ownership of the data
- The original object won't be used again
- You want maximum efficiency for expensive-to-copy objects */

void processVector(std::vector<int> vec) {
    std::cout << "Vector size in function: " << vec.size() << std::endl;
}



int main() {
    std::vector<int> myData = {1, 2, 3, 4, 5};
    analyzeData(myData);    // myData still has 5 elements after call

    // Example 1: Moving object into function
    std::vector<int> nums = {1, 2, 3, 4, 5};
    DataContainer container("MyData", std::move(nums));
    
    std::cout << "Original vector size after move: " << nums.size() << std::endl;
    
    // Move container into function
    processData(std::move(container));
    
    // Example 2: Moving vector directly
    std::vector<int> bigVector(1000, 42);
    std::cout << "Vector size before move: " << bigVector.size() << std::endl;
    
    processVector(std::move(bigVector));
    
    std::cout << "Vector size after move: " << bigVector.size() << std::endl;
    
    return 0;
}