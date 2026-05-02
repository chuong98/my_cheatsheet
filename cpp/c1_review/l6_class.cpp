#include <iostream>

class Test {
private:
    int a;
    int b;
    
public:
    // Constructor
    Test(int a_val = 0, int b_val = 0) : a(a_val), b(b_val) {}
    Test(const int &a_val, const int &b_val) : a(a_val), b(b_val) {
        std::cout << "Constructor with two const int references called" << std::endl;
    }

    // Copy constructor: always take one const argument
    // This is used to create a new object as a copy of an existing object
    // It is called when passing objects by value or returning objects from functions
    Test(const Test &source) : a(source.a), b(source.b) {
        std::cout << "Copy constructor get only one input" << std::endl;
    }

    // Assignment operator: used to copy the values from one object to another
    // It is called when an existing object is assigned a new value
    // It returns a reference to the current object
    Test& operator=(const Test &source) {
        if (this == &source) return *this; // self-assignment check
        a = source.a;
        b = source.b;
        std::cout << "Assignment operator called" << std::endl;
        return *this;
    }

    // Destructor: clean up resources when the object goes out of scope
    // It is called automatically when an object is destroyed
    // It does not take any parameters and does not return a value
    ~Test() {
        std::cout << "Destructor called for object with values a=" << a << ", b=" << b << std::endl;
    }
    
    // Function to add two variables and print the result
    void addAndPrint() {
        int sum = a + b;
        std::cout << "Sum of " << a << " and " << b << " is: " << sum << std::endl;
    }
    
    // Setters
    void setA(int value) { a = value; }
    void setB(int value) { b = value; }
};

int main() {
    Test t1(10, 20);
    t1.addAndPrint();
    
    Test t2;
    t2.setA(5);
    t2.setB(15);
    t2.addAndPrint();
    
    return 0;
}