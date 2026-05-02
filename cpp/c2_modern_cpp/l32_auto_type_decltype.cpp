#include <iostream>
#include <vector>
#include <map>
#include <string>
/* 
1. auto type is useful in declaration complex types, iterators, and lambda expressions
  -It allows the compiler to deduce the type automatically, making the code cleaner and more maintainable.
2. decltype takes an expression and deduces its type, which can be useful for declaring variables with the same type as another variable or expression.
  -It is particularly useful when you want to declare a variable with the same type as another variable or expression.
  - decltype(f()) z;
3. auto and decltype are both used for type deduction, but auto is used for variable declarations while decltype is used for type inference based on an expression.
  
*/


int main() {
    // Basic auto usage
    auto x = 42;           // int
    auto y = 3.14;         // double
    auto z = 'a';          // char
    auto str = "Hello";    // const char*
    
    std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
    
    // Auto with containers
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    auto vec = numbers;    // std::vector<int>
    
    // Auto with iterators (much cleaner)
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Auto with complex types
    std::map<std::string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    
    // Without auto (verbose)
    // std::map<std::string, int>::iterator iter = ages.begin();
    
    // With auto (clean)
    auto iter = ages.begin();
    
    // Auto with function return types
    auto lambda = [](int a, int b) -> int { return a + b; };
    auto result = lambda(5, 3);
    
    std::cout << "Lambda result: " << result << std::endl;
    
    // Auto with references
    auto& ref = x;         // int&
    const auto& const_ref = y;  // const double&
    
    // decltype usage
    decltype(x) a = 10;   // a is of type int
    decltype(str) b = "World"; // b is of type const char*
    return 0;
}