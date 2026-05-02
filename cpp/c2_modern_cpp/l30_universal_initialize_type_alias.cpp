#include <iostream>
#include <vector>
#include <string>
#include <map>

class Person {
public:
    std::string name;
    int age;
    
    Person(const std::string& n, int a) : name(n), age(a) {}
};

int main() {
    //--------------------------------------
    // Universal initialization (uniform initialization) using braces {}
    
    // Basic types
    int x{42};
    double pi{3.14159};
    char c{'A'};
    
    // Arrays
    int arr[]{1, 2, 3, 4, 5};
    
    // STL containers
    std::vector<int> vec{10, 20, 30, 40};
    std::vector<std::string> names{"Alice", "Bob", "Charlie"};
    
    // Map initialization
    std::map<std::string, int> ages{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    
    // Class objects
    Person person1{"John Doe", 28};
    Person person2{"Jane Smith", 32};
    
    // Dynamic allocation
    auto ptr = new Person{"Mike Johnson", 45};
    
    // Prevent narrowing conversions (compile error)
    // int narrow{3.14}; // Error: narrowing conversion
    
    // Print some values
    std::cout << "x: " << x << std::endl;
    std::cout << "Person: " << person1.name << ", " << person1.age << std::endl;
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    delete ptr;
    //--------------------------------------

    //1. using type alias to simplify declaration
    using IntVector = std::vector<int>;
    using StringMap = std::map<std::string, int>;

    IntVector numbers{1, 2, 3, 4, 5};
    StringMap nameToAge{
        {"Alice", 25},
        {"Bob", 30}
    };

    std::cout << "Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}