#include <iostream>

enum class Color {
    RED,
    GREEN,
    BLUE
};

enum class Status {
    PENDING,
    APPROVED,
    REJECTED
};

void printColor(Color color) {
    switch (color) {
        case Color::RED:
            std::cout << "Red" << std::endl;
            break;
        case Color::GREEN:
            std::cout << "Green" << std::endl;
            break;
        case Color::BLUE:
            std::cout << "Blue" << std::endl;
            break;
    }
}

int main() {
    Color myColor = Color::RED;
    Status myStatus = Status::APPROVED;
    
    printColor(myColor);
    
    // enum class won't implicitly convert to int or other types
    // This is a key feature of enum class to prevent accidental misuse.
    // For example, you cannot do this:
    // int colorValue = myColor; // Error: cannot convert 'Color' to 'int'
    
    // You must explicitly cast it if needed:
    if (myColor == Color::RED) {
        std::cout << "The color is red." << std::endl;
    }

    // Type safety - this won't compile:
    // if (myColor == myStatus) { }  // Error: different enum types
    
    // Explicit conversion needed:
    int colorValue = static_cast<int>(myColor);
    std::cout << "Color value: " << colorValue << std::endl;


    
    return 0;
}