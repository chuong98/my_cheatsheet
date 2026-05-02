#include <iostream>
#include <vector>
#include <stdexcept>


/* -noexcept is a promise to the caller:
- either the function will not throw exceptions, 
- or it will be a logic error if it does. Then, the program terminate immediately.

noexcept helpds the compiler optimize code by avoiding unnecessary exception handling overhead.
- It can also be used to enable move semantics, as move constructors and move assignment operators are often marked as noexcept.
- noexcept can be applied to functions, methods, and even lambda expressions.
- It can also be used with templates to conditionally mark functions as noexcept based on type traits.

- noexcept is inherited:
    + if the a virtual function is noexcept, then all derived classes must also be noexcept.
    + inherited constructors will be noexcept if the base class constructor is noexcept.
 */

 // Function that guarantees no exceptions
int add(int a, int b) noexcept {
    return a + b;
}

// Function that may throw exceptions
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

// Function with conditional noexcept
template<typename T>
void swap_values(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Class with noexcept methods
class Calculator {
public:
    Calculator() noexcept = default;
    ~Calculator() noexcept = default;
    
    int multiply(int a, int b) noexcept {
        return a * b;
    }
    
    // Move constructor marked as noexcept
    Calculator(Calculator&& other) noexcept = default;
    Calculator& operator=(Calculator&& other) noexcept = default;
};

int main() {
    // Using noexcept functions
    int result = add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;
    
    Calculator calc;
    std::cout << "4 * 6 = " << calc.multiply(4, 6) << std::endl;
    
    // Check if functions are noexcept at compile time
    static_assert(noexcept(add(1, 2)), "add should be noexcept");
    static_assert(!noexcept(divide(1, 2)), "divide should not be noexcept");
    
    // Using swap with noexcept
    int x = 10, y = 20;
    swap_values(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    return 0;
}