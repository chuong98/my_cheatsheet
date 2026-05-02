#include <iostream>
#include <utility>
#include <tuple>
#include <string>

int main() {
    // ========== PAIR EXAMPLES ==========
    std::cout << "=== PAIR EXAMPLES ===" << std::endl;
    
    // Creating pairs
    std::pair<int, std::string> p1(42, "Hello");
    auto p2 = std::make_pair(3.14, "World");
    
    // Accessing pair elements
    std::cout << "p1.first: " << p1.first << ", p1.second: " << p1.second << std::endl;
    std::cout << "p2.first: " << p2.first << ", p2.second: " << p2.second << std::endl;
    
    // Using structured bindings (C++17)
    auto [value, text] = p1;
    std::cout << "Structured binding - value: " << value << ", text: " << text << std::endl;
    
    // ========== TUPLE EXAMPLES ==========
    std::cout << "\n=== TUPLE EXAMPLES ===" << std::endl;
    
    // Creating tuples
    std::tuple<int, double, std::string> t1(10, 2.5, "Tuple");
    auto t2 = std::make_tuple(20, 'A', true, 99.9);
    
    // Accessing tuple elements using std::get
    std::cout << "t1 elements: " << std::get<0>(t1) << ", " 
              << std::get<1>(t1) << ", " << std::get<2>(t1) << std::endl;
    
    // Using structured bindings with tuple (C++17)
    auto [num, letter, flag, decimal] = t2;
    std::cout << "Structured binding - num: " << num << ", letter: " << letter 
              << ", flag: " << flag << ", decimal: " << decimal << std::endl;
    
    // Getting tuple size
    std::cout << "t2 size: " << std::tuple_size_v<decltype(t2)> << std::endl;
    
    // ========== PRACTICAL EXAMPLES ==========
    std::cout << "\n=== PRACTICAL EXAMPLES ===" << std::endl;
    
    // Function returning multiple values using tuple
    auto getDivisionResult = [](int a, int b) -> std::tuple<int, int, bool> {
        if (b == 0) return {0, 0, false};
        return {a / b, a % b, true};
    };
    
    auto [quotient, remainder, success] = getDivisionResult(17, 5);
    if (success) {
        std::cout << "17 / 5 = " << quotient << " remainder " << remainder << std::endl;
    }
    
    // Using pair for key-value storage
    std::pair<std::string, int> keyValue("age", 25);
    std::cout << "Key: " << keyValue.first << ", Value: " << keyValue.second << std::endl;
    
    return 0;
}