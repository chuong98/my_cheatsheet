#include <iostream>
#include <vector>
#include <algorithm>

/* Lambda expressions in C++
- lambda is an anonymous function.
- To define a lambda, use the syntax: [captures](parameters) -> return_type { body }, where 
    + [] is used for the function name
    + captures are optional variables from the surrounding scope that you want to use in the lambda. It is stored as the private member of the lambda object.
    + captures can be by value (e.g., [x]) or by reference (e.g., [&x])
    + parameters are the inputs to the lambda as in a regular function
    + return_type is optional; if omitted, the return type is deduced automatically
    + body contains the code to be executed when the lambda is called
*/

bool equal_strings(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                      [](char lhs, char rhs) { return std::tolower(lhs) == std::tolower(rhs); });
}

void test_lambda(const std::string& str1, const std::string& str2) {
    std::cout << str1 << " and " << str2 
              << (equal_strings(str1, str2) ? " are equal (case-insensitive)." : " are not equal (case-insensitive).") 
              << std::endl;
}
int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Count even numbers using lambda expression
    int evenCount = std::count_if(numbers.begin(), numbers.end(), 
                                  [](int n) { return n % 2 == 0; });
    
    std::cout << "Even numbers count: " << evenCount << std::endl;
    
    // Count numbers greater than 5
    int max{5};
    std::cout << "Max value: " << max << std::endl;
    int greaterThanMax = std::count_if(numbers.begin(), numbers.end(),
                                        [max](int n) { return n > max; });

    std::cout << "Numbers > 5: " << greaterThanMax << std::endl;

    // Check if two strings are equal ignoring case
    test_lambda("Hello", "hello");
    test_lambda("World", "worlds");
    
    // Using lambda to sort a vector of pairs by the second element
    std::vector<std::pair<int, std::string>> vec = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
    std::sort(vec.begin(), vec.end(), 
              [](const auto& a, const auto& b) { return a.second < b.second; });
    
    std::cout << "Sorted pairs by second element:" << std::endl;
    for (const auto& p : vec) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
    return 0;

}