#include <iostream>
#include <initializer_list>
#include <vector>
/* 
initializer_list is useful for passing a variable number of arguments to a function.
- It is a lightweight alternative to using vectors or arrays when you just need to pass a list of values.
- It can be used with any type that supports copy or move construction.
- It is often used in constructors, function parameters, and algorithms that require a list of values.
*/

// Function that takes an initializer_list
void print_numbers(std::initializer_list<int> numbers) {
    std::cout << "Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function that returns the sum of values in initializer_list
int calculate_sum(std::initializer_list<int> values) {
    int sum = 0;
    for (const auto& value : values) {
        sum += value;
    }
    return sum;
}

// Function that creates a vector from initializer_list
std::vector<int> create_vector(std::initializer_list<int> elements) {
    return std::vector<int>(elements);
}

class Test{
public:
    Test(std::initializer_list<int> values) : data(values) {}

    void print() const {
        for (const auto& value : data) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> data;
};

int main() {
    // Using initializer_list with functions
    print_numbers({1, 2, 3, 4, 5});
    
    int sum = calculate_sum({10, 20, 30, 40});
    std::cout << "Sum: " << sum << std::endl;
    
    auto vec = create_vector({100, 200, 300});
    std::cout << "Vector size: " << vec.size() << std::endl;

    Test testObj = {1, 2, 3, 4, 5};
    testObj.print();

    return 0;
}