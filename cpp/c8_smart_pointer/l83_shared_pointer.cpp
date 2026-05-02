#include <iostream>
#include <memory>

class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Person " << name << " created\n";
    }
    
    ~Person() {
        std::cout << "Person " << name << " destroyed\n";
    }
    
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    std::string getName() const { return name; }
};


/* Shared pointer allows different objects to share a single memory allocation.
- shared pointer releases the memory when the last reference is destroyed
- shared pointer supports the same operations that unique_ptr does, plus copy and assignment */
int main() {
    // Creating shared_ptr
    std::shared_ptr<Person> ptr1 = std::make_shared<Person>("Alice", 25);
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    {
        // Copying shared_ptr increases reference count
        std::shared_ptr<Person> ptr2 = ptr1;
        std::cout << "Reference count after copy: " << ptr1.use_count() << std::endl;
        
        ptr2->display();
    } // ptr2 goes out of scope, reference count decreases
    
    std::cout << "Reference count after ptr2 destroyed: " << ptr1.use_count() << std::endl;
    ptr1->display();
    
    // Reset the pointer
    ptr1.reset();
    std::cout << "ptr1 reset, object should be destroyed now\n";
    
    return 0;
}