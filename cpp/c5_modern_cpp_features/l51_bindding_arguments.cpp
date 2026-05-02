#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

bool greater_than(int value, int threshold) {
    return value > threshold;
}

int main() {
    std::vector<int> numbers = {1, 5, 8, 12, 3, 9, 15, 2};
    
    // Using std::bind to bind the second argument (threshold) to 7
    auto bound_function = std::bind(greater_than, std::placeholders::_1, 7);
    
    // Count elements greater than 7
    int count = std::count_if(numbers.begin(), numbers.end(), bound_function);
    
    std::cout << "Numbers greater than 7: " << count << std::endl;
    
    // Alternative: using lambda (more modern approach)
    int count_lambda = std::count_if(numbers.begin(), numbers.end(), 
                                   [](int x) { return x > 7; });
    
    std::cout << "Using lambda - Numbers greater than 7: " << count_lambda << std::endl;
    
    return 0;
}