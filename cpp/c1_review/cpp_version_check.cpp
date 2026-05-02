#include <iostream>

int main() {
    std::cout << "C++ Standard Version Information:" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // Check __cplusplus macro value
    std::cout << "__cplusplus macro value: " << __cplusplus << std::endl;
    
    // Determine C++ standard based on __cplusplus value
    #if __cplusplus >= 202302L
        std::cout << "C++ Standard: C++23 or later" << std::endl;
    #elif __cplusplus >= 202002L
        std::cout << "C++ Standard: C++20" << std::endl;
    #elif __cplusplus >= 201703L
        std::cout << "C++ Standard: C++17" << std::endl;
    #elif __cplusplus >= 201402L
        std::cout << "C++ Standard: C++14" << std::endl;
    #elif __cplusplus >= 201103L
        std::cout << "C++ Standard: C++11" << std::endl;
    #else
        std::cout << "C++ Standard: Pre-C++11" << std::endl;
    #endif
    
    // Check for specific feature availability
    #ifdef __cpp_concepts
        std::cout << "Concepts support: YES (C++20 feature)" << std::endl;
    #else
        std::cout << "Concepts support: NO" << std::endl;
    #endif
    
    #ifdef __cpp_modules
        std::cout << "Modules support: YES (C++20 feature)" << std::endl;
    #else
        std::cout << "Modules support: NO" << std::endl;
    #endif
    
    #ifdef __cpp_coroutines
        std::cout << "Coroutines support: YES (C++20 feature)" << std::endl;
    #else
        std::cout << "Coroutines support: NO" << std::endl;
    #endif
    
    return 0;
}
