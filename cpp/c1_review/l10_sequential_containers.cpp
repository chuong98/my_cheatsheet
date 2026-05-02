#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <string>

int main() {
    /*
     Sequential containers in C++ are used to store collections of objects in a linear order.
     They provide various functionalities to manage and manipulate these collections.
     The most commonly used sequential containers are:
        - std::vector: A dynamic array that can grow in size.
        - std::deque: A double-ended queue that allows insertion and deletion at both ends.
    + any element can be accessed in constant time. Optimized for jumping to any element.
    + Removal of elements is efficient at the end, but can be slow in the middle.

    Another sequential containers include:
        - std::queue: A container adapter that provides a FIFO (First In First Out) data structure.
        - std::stack: A container adapter that provides a LIFO (Last In First Out) data structure.
        - std::priority_queue: A container adapter that provides a priority queue data structure.
    + Only element at the front can be accessed.
    + Removal of elements is efficient at the top, but can be slow in the middle.
    + priority_queue is a special type of queue where elements are ordered by priority. 
    + priority_queue uses top() to access the highest priority element, it does not have front() or back() methods.

    Another important sequential containers include:
        - std::list: A doubly linked list that allows fast insertion and deletion from both ends.
        - std::forward_list: A singly linked list that allows fast insertion and deletion from the front.
    + can only iterate from one element to the next. cannot jump to any element.
    + Insert and removing elements take equal time at any position. Optimized for insertion and deletion.

    */
    // Vector example
    std::cout << "=== Vector Example ===" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.insert(vec.begin() + 2, 10);
    vec.push_back(6); //copying the element to the end
    vec.emplace_back(7); // emplace_back() constructs objects in-place directly in the vector, while push_back() copies or moves an existing object.

    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    // Deque example
    std::cout << "\n=== Deque Example ===" << std::endl;
    std::deque<std::string> deq = {"middle"};
    deq.push_front("front");
    deq.push_back("back");
    deq.push_front("very_front");
    
    std::cout << "Deque elements: ";
    for (const auto& element : deq) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    std::cout << "First element: " << deq.front() << std::endl;
    std::cout << "Last element: " << deq.back() << std::endl;
    
    // Stack example
    std::cout << "\n=== Stack Example ===" << std::endl;
    std::stack<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
    std::cout << "Stack size: " << stk.size() << std::endl;
    std::cout << "Popping elements: ";
    while (!stk.empty()) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::cout << std::endl;
    
    return 0;
}