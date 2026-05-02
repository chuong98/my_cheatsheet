#include <iostream>

int func_pass_by_value(int x) {
    x = 20; // Modify the local copy
    return x;
}

int func_pass_by_value_ref(int &x) {
    x = 30; // Modify the original variable
    return x;
}

int func_pass_by_value_const_ref(const int &x) {
    // for read only, pass by const reference is more efficient since it avoids copying
    // x = 40; // This would cause a compilation error
    return x + 10; // Just return a modified value
}

int func_pass_by_pointer(int *x) {
    // pass by pointer need to deference
    // a pointer can be nullptr
    if (x) {
        *x = 50; // Modify the value at the address
    }
    return x ? *x : 0;
}

int main() {
    int a = 5;
    std::cout << "Initial value of a: " << a << std::endl;

    int result1 = func_pass_by_value(a);
    std::cout << "After func_pass_by_value, a: " << a << ", result: " << result1 << std::endl;

    int result2 = func_pass_by_value_ref(a);
    std::cout << "After func_pass_by_value_ref, a: " << a << ", result: " << result2 << std::endl;

    int result3 = func_pass_by_value_const_ref(a);
    std::cout << "After func_pass_by_value_const_ref, a: " << a << ", result: " << result3 << std::endl;

    int result4 = func_pass_by_pointer(&a);
    std::cout << "After func_pass_by_pointer, a: " << a << ", result: " << result4 << std::endl;

    return 0;
}
// This program demonstrates different ways of passing variables to functions in C++: