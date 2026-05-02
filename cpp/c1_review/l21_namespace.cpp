#include <iostream>
#include <string>

// Define a custom namespace
namespace Math {
    const double PI = 3.14159;
    
    double calculateArea(double radius) {
        return PI * radius * radius;
    }
    
    double calculateCircumference(double radius) {
        return 2 * PI * radius;
    }
}

namespace Utils {
    void printMessage(const std::string& message) {
        std::cout << "Message: " << message << std::endl;
    }
}

int main() {
    // Using namespace with scope resolution operator
    double radius = 5.0;
    double area = Math::calculateArea(radius);
    double circumference = Math::calculateCircumference(radius);
    
    std::cout << "Area: " << area << std::endl;
    std::cout << "Circumference: " << circumference << std::endl;
    
    // Using namespace
    using namespace Utils;
    printMessage("Hello from Utils namespace!");
    
    // Using specific function from namespace
    using Math::PI;
    std::cout << "PI value: " << PI << std::endl;
    
    return 0;
}