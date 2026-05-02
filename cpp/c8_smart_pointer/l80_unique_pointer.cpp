#include <iostream>
#include <memory>
#include <vector>

/* the advantage of unique_ptr:
- Automatic memory management
- No need to explicitly delete memory
- Prevents memory leaks
- Cannot be copied, only moved (unique ownership)

unique_pt is used in polymorphic types
*/
class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Person " << name << " created" << std::endl;
    }
    
    ~Person() {
        std::cout << "Person " << name << " destroyed" << std::endl;
    }
    
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};


class base_shape {
public:
    virtual void print() const = 0; // pure virtual function
    virtual ~base_shape() = default; // virtual destructor
};

class circle : public base_shape {
public:
    void print() const override {
        std::cout << "This is a circle" << std::endl;
    }
    ~circle() {
        std::cout << "Circle destroyed" << std::endl;
    }
};

class square : public base_shape {
public:
    void print() const override {
        std::cout << "This is a square" << std::endl;
    }
    ~square() {
        std::cout << "Square destroyed" << std::endl;
    }
};

// Example of using unique_ptr with polymorphic types

int main() {
    // Creating unique_ptr using new (C++11)
    std::unique_ptr<Person> person2(new Person("Bob", 30));
    person2->display();

    // Creating unique_ptr using make_unique (C++14)
    std::unique_ptr<Person> person1 = std::make_unique<Person>("Alice", 25);
    person1->display();

    // using auto type deduction with unique_ptr
    // This is a cleaner way to create unique_ptr
    auto person3 = std::make_unique<Person>("Charlie", 35);
    person3->display();

    // Moving ownership
    std::unique_ptr<Person> person4 = std::move(person1);
    // person1 is now nullptr
    
    if (person1 == nullptr) {
        std::cout << "person1 is nullptr after move" << std::endl;
    }
    
    person4->display();
    
    // Releasing ownership
    Person* rawPtr = person2.release();
    std::cout << "Released ownership, manual cleanup required" << std::endl;
    delete rawPtr; // Manual cleanup needed
    

    // Using unique_ptr with polymorphic types
    std::vector<std::unique_ptr<base_shape>> shapes;
    shapes.push_back(std::make_unique<circle>());
    shapes.push_back(std::make_unique<square>());

    for (const auto& shape : shapes) {
        shape->print();
    }

    return 0;
    // person3 automatically destroyed when going out of scope
}