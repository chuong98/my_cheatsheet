#include <iostream>
#include <string>

/* 
- One template declaration per template entity (function or class)
- The template declaration applies to the entire class definition that follows
- If you separate declaration and implementation, you'd need the template syntax for both, but that's a different scenario
- Templates in C++ are typically defined entirely in header files because the compiler needs to see the full implementation to generate code for specific types (like Container<int> or Container<string>). */
// Template function example
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// Template class example
template <typename T>
class Container {
private:
    T data;
    
public:
    Container(T value) : data(value) {}
    
    void setData(T value) {
        data = value;
    }
    
    T getData() const {
        return data;
    }
    
    void display() const {
        std::cout << "Data: " << data << std::endl;
    }
};

int main() {
    // Using template function
    std::cout << "Max of 10 and 20: " << getMax(10, 20) << std::endl;
    std::cout << "Max of 3.14 and 2.71: " << getMax(3.14, 2.71) << std::endl;
    std::cout << "Max of 'a' and 'z': " << getMax('a', 'z') << std::endl;
    
    // Using template class
    Container<int> intContainer(42);
    Container<std::string> stringContainer("Hello");
    Container<double> doubleContainer(99.99);
    
    intContainer.display();
    stringContainer.display();
    doubleContainer.display();
    
    // Modifying data
    intContainer.setData(100);
    stringContainer.setData("World");
    
    std::cout << "Updated values:" << std::endl;
    intContainer.display();
    stringContainer.display();
    
    return 0;
}