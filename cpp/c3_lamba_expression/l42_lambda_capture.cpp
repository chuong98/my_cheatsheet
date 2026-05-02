#include <iostream>

/* Mutable lambda example
- by default,  [captures] are copied to the lambda's scope, and we can't modify them.
- adding 'mutable' allows us to modify the captured variables inside the lambda.
- but the changes are not reflected outside the lambda.
- to modify the outer variable, we need to capture it by reference.

Capture all variables by value or reference:
- [=] captures all variables by value, [&] captures all variables by reference.
- it is usually better to capture only the variables you need, either by value or by reference.
- [&,=a,=b] captures all variables by reference except 'a' and 'b', which are captured by value.
- [=, &a, &b] captures all variables by value except 'a' and 'b', which are captured by reference.

Lambda function in a class can use "this" pointer to access class members.

*/
int main() {
    // Example 1: Mutable lambda with capture by value
    int t = 10;

    auto lambda1 = [t]() mutable {
        t += 5;  // Without mutable, this would be a compile error
        std::cout << "Inside lambda: t = " << t << std::endl;
        return t;
    };
    
    std::cout << "Before calling lambda: t = " << t << std::endl;
    int result = lambda1();
    std::cout << "After calling lambda: t = " << t << std::endl; // x remains unchanged outside the lambda
    std::cout << "Lambda returned: " << result << std::endl;    // result is 15, x(a copy version) inside lambda is modified but not the outer x
    
    std::cout << "\n--- Example 2 ---\n";
    
    // Example 2: Mutable lambda with reference captures
    int a = 1, b = 2;

    auto lambda2 = [&a, &b](int increment) mutable -> int {
        a += increment;
        b += increment;
        std::cout << "Inside lambda: a = " << a << ", b = " << b << std::endl;
        return a + b;
    };

    std::cout << "Original values: a = " << a << ", b = " << b << std::endl;
    int sum = lambda2(10);
    std::cout << "After lambda call: a = " << a << ", b = " << b << std::endl;
    std::cout << "Sum returned: " << sum << std::endl;

    // Example 3: using this pointer in a class
    class MyClass {
    public:
        int value = 5;

        void demonstrateLambda() {
            [this]() {
                std::cout << "Value from class: " << this->value << std::endl;
            }(); //calling the lambda immediately
        }
    };
    
    std::cout << "\n--- Example 3 ---\n";
    MyClass obj;
    obj.demonstrateLambda();

    // example 4: Capture all variables by value and reference
    int x{42}, y{99}, z{0};
    std::cout << "Before lambda call: x = " << x << ", y = " << y << ", z = " << z << std::endl; // x and y are unchanged, z is 0
 
    auto lam = [=,&z]() mutable { ++x; ++y; z = x + y; };
    lam();
    std::cout << "\n--- Example 4 ---\n";
    std::cout << "After lambda call: x = " << x << ", y = " << y << ", z = " << z << std::endl; // x and y are unchanged, z is modified
    return 0;
}