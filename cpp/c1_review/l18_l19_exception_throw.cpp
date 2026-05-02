#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return a / b;
}

int main() {
    try {
        int result1 = divide(10, 2);
        std::cout << "10 / 2 = " << result1 << std::endl;
        
        int result2 = divide(10, 0);  // This will throw an exception
        std::cout << "10 / 0 = " << result2 << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    // we can have many catch blocks for different exception types.
    // catch the standard exception type to handle all standard exceptions.
    // This is useful for catching exceptions that are derived from std::exception.
    // It is a good practice to catch specific exceptions first, then catch the general std::exception.
    catch (const std::exception& e) {
        std::cout << "Standard exception caught: " << e.what() << std::endl;
    }
    // catch (...) Catch-all handler for any other exceptions
    // This is useful for unexpected exceptions that are not derived from std::exception.
    // It is a good practice to have this at the end of your catch blocks.
    catch (...) {
        std::cout << "Unknown error occurred!" << std::endl;
    }
    
    std::cout << "Program continues after exception handling" << std::endl;
    
    return 0;
}