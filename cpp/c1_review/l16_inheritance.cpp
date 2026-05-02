#include <iostream>
#include <string>

/*  Base class
- private members are not accessible in derived classes.
- protected members are accessible in derived classes but not outside the class hierarchy.
- public members are accessible anywhere.
- virtual functions can be overridden in derived classes.

- What is meant by "overloading" a member function?

Overloading allows us to define two or more functions which have the same name but have a different signature. Usually this is because we want to call the same function, but with different arguments.
To overload a member function, we add another function in the same class. This new member function has the same name but has a different signature.

- What is meant by "overriding" a member function?
Overriding is used to implement polymorphism in C++.
We make a member function virtual in the base class, then "override" it in child classes. This allows us to implement each child in a different way, while providing a common interface. If we call a virtual function through a pointer or a reference to the base class, the correct version for the child class will be called.
To override a member function, first we must declare it virtual in the parent class.
We then add a member function in a child class. This has the same name as the parent class function and takes the same arguments.


 */
class Animal {
protected:
    std::string name;
    int age;

public:
    Animal(const std::string& n, int a) : name(n), age(a) {}
    
    // virtual function to allow derived classes to override it:
    // any type of derived class can override this method.
    // usually the virtual function is defined but not implemented in the base class.

    virtual void makeSound() const=0; // pure virtual function, making this an abstract class
    virtual ~Animal() = default; // virtual destructor for proper cleanup of derived classes. 
    // if we don't provide a virtual destructor, the compiler will provide a non-virtual default destructor.
    // Dangerous::: so always provide a virtual destructor in base classes.
    
    // non-virtual function
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

/* Derived class:
- can access the public and protected data members of the base class.
- the derived class can call the non-private member functions of the base class using the scope resolution operator (::).
 + It can override base class methods.
 + It can overload base class methods by calling the base class and then add more code before/after.
- It can add new member functions and data members.
 */
class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(const std::string& n, int a, const std::string& b) 
        : Animal(n, a), breed(b) {}
    
    void makeSound() const override {
        std::cout << name << " barks: Woof!" << std::endl;
    }
    
    void wagTail() const {
        std::cout << name << " is wagging tail" << std::endl;
    }
};


class Cat : public Animal {
private:
    std::string color;

public:
    Cat(const std::string& n, int a, const std::string& c) 
        : Animal(n, a), color(c) {}
    
    void makeSound() const override {
        std::cout << name << " meows: Meow!" << std::endl;
    }
    
    void scratch() const {
        std::cout << name << " is scratching" << std::endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden Retriever");
    Cat cat("Whiskers", 2, "Tabby");

    dog.displayInfo();
    dog.makeSound();
    dog.wagTail();

    cat.displayInfo();
    cat.makeSound();
    cat.scratch();

    // Demonstrating polymorphism: Using a base class pointer to refer to derived class objects.
    std::cout << "\nUsing base class pointer to refer to derived class objects:" << std::endl;
    Animal* animalPtr;

    animalPtr = &dog;
    animalPtr->displayInfo();
    animalPtr->makeSound();

    animalPtr = &cat;
    animalPtr->displayInfo();
    animalPtr->makeSound();
    
    // container of derived class using base class pointer
    std::cout << "\nUsing polymorphism with a vector of Animal pointers:" << std::endl;
    std::vector<Animal*> animals;
    animals.push_back(&dog);
    animals.push_back(&cat);

    for (const auto& animal : animals) {
        animal->displayInfo();
        animal->makeSound();
        // check class type at runtime using dynamic_cast
        // This is useful when you want to call derived class specific methods.
        // If the cast fails, it returns nullptr.
        std::cout << "Checking type:" << std::endl;
        if (Dog* dog_ptr = dynamic_cast<Dog*>(animal)) {
            std::cout << "This is a Dog." << std::endl;
            dog_ptr->wagTail();
        } else if (Cat* cat_ptr = dynamic_cast<Cat*>(animal)) {
            std::cout << "This is a Cat." << std::endl;
            cat_ptr->scratch();
        }
    }


    return 0;
}