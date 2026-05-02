#include <iostream>
class Base {
protected:
    int value;

public:
    Base(int v = 0) : value(v) {}

    virtual void print() const {
        std::cout << "Base class." << std::endl;
    }
};

class Child : public Base {
public:
    void print() const override {
        std::cout << "Child class." << std::endl;
    }
};

class GrandChild : public Child {
public:
    void print() const override {
        std::cout << "GrandChild class." << std::endl;
    }
};

// void print_class(const Base* obj) {
//     obj->print();
// }

void print_class(const Base& obj) {
    obj.print();
}

int main() {
    Base* basePtr = new Base();
    Child* childPtr = new Child();
    GrandChild* grandChildPtr = new GrandChild();

    print_class(*basePtr);
    print_class(*childPtr);
    print_class(*grandChildPtr);

    delete basePtr;
    delete childPtr;
    delete grandChildPtr;

    return 0;
}
