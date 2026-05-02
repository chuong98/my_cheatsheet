#include <iostream>
#include <string>

// Inline namespace for current API version
namespace MyLibrary {
    inline namespace v2 {
        class Calculator {
        public:
            int add(int a, int b) {
                return a + b;
            }
            
            std::string getVersion() {
                return "v2.0";
            }
        };
        
        void printMessage() {
            std::cout << "Using v2 API\n";
        }
    }
    
    // Old version (not inline)
    namespace v1 {
        class Calculator {
        public:
            int add(int a, int b) {
                std::cout << "Legacy add function\n";
                return a + b;
            }
            
            std::string getVersion() {
                return "v1.0";
            }
        };
        
        void printMessage() {
            std::cout << "Using v1 API\n";
        }
    }
}

int main() {
    // Uses v2 (inline namespace) by default
    MyLibrary::Calculator calc;
    std::cout << "Result: " << calc.add(5, 3) << std::endl;
    std::cout << "Version: " << calc.getVersion() << std::endl;
    MyLibrary::printMessage();
    
    // Explicitly use v1
    MyLibrary::v1::Calculator oldCalc;
    std::cout << "Old result: " << oldCalc.add(5, 3) << std::endl;
    std::cout << "Old version: " << oldCalc.getVersion() << std::endl;
    MyLibrary::v1::printMessage();
    
    return 0;
}