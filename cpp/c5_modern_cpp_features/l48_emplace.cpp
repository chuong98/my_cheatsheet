#include <iostream>
#include <vector>
#include <string>

class Person {
public:
    std::string name;
    int age;
    
    // Constructor
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Person constructor called for " << name << std::endl;
    }
    
    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Person copy constructor called for " << name << std::endl;
    }
    
    // Move constructor
    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
        std::cout << "Person move constructor called for " << name << std::endl;
    }
    
    // Copy assignment operator
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            std::cout << "Person copy assignment called for " << name << std::endl;
        }
        return *this;
    }
    
    // Move assignment operator
    Person& operator=(Person&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
            std::cout << "Person move assignment called for " << name << std::endl;
        }
        return *this;
    }
};

int main() {
    std::vector<Person> people;
    
    //use insert() to add elements at a specific position
    std::cout << "=== Using insert() ===" << std::endl;
    people.insert(people.begin(), Person("Alice1", 25));  // Inserts at the beginning
    people.insert(people.end(), Person("Bob1", 30));      // Inserts at the end

    //use emplace() to construct objects in place
    std::cout << "=== Using emplace() ===" << std::endl;
    people.emplace(people.begin(), "Charlie2", 35);  // Constructs Person directly in vector
    people.emplace(people.end(), "David2", 40);
    
    // Demonstrating push_back() and emplace_back()
    std::cout << "\n=== Using push_back (creates temporary then copies/moves) ===" << std::endl;
    people.push_back(Person("Chuong3", 35));  // Creates temporary, then moves
    people.push_back({"Danie3", 40});          // Creates temporary, then moves

    // Using emplace_back() to construct directly in vector
    std::cout << "=== Using emplace_back (constructs in place) ===" << std::endl;
    people.emplace_back("Alice4", 25);  // Constructs Person directly in vector
    people.emplace_back("Bob4", 30);


    std::cout << "\n=== Vector contents ===" << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ")" << std::endl;
    }
    
    return 0;
}