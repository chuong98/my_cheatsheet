#include <iostream>
#include <string>
#include <format>


/* Overload operators are used to define custom behavior for operators like +, -, *, /, ==, !=, <, >, <=, >=, etc.
AN example is to sort objects of a class based on their attributes in a vector or a map.
*/

class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    // Equality operator
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
    
    // Inequality operator
    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
    
    // Less than operator
    bool operator<(const Person& other) const {
        if (age != other.age) {
            return age < other.age;
        }
        return name < other.name;
    }
    
    // Greater than operator
    bool operator>(const Person& other) const {
        return other < *this;
    }
    
    // Less than or equal operator
    bool operator<=(const Person& other) const {
        return !(other < *this);
    }
    
    // Greater than or equal operator
    bool operator>=(const Person& other) const {
        return !(*this < other);
    }
    
    // Stream insertion operator (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " (age: " << p.age << ")";
        return os;
    }

    //callable operator
    void operator()(const int &weight) const {
        // std::cout << "Person " << name << " is " << age << " years old and weighs " << weight << " kg." << std::endl;
        std::cout << std::format("Person {} is {} years old and weighs {} kg.\n", name, age, weight);
    }
};

int main() {
    Person p1("Alice", 25);
    Person p2("Bob", 30);
    Person p3("Alice", 25);
    
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;
    
    std::cout << "\nComparisons:" << std::endl;
    std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
    std::cout << "p2 > p1: " << (p2 > p1) << std::endl;
    std::cout << "p1 <= p3: " << (p1 <= p3) << std::endl;
    std::cout << "Use callable operator p1(50): ";
    p1(50); // calling the callable operator with weight 50
    return 0;
}