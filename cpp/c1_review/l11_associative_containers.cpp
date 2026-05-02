#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
/**
 * Demonstrates the usage of C++ associative containers with their key characteristics.
 * 
 * This program showcases four main associative container types:
 * 
 * 1. std::set - Stores unique elements in sorted order (typically implemented as red-black tree)
 *    - Automatically removes duplicates
 *    - Elements are sorted by default comparison operator
 *    - O(log n) insertion, deletion, and search
 * 
 * 2. std::map - Key-value pairs sorted by key (typically implemented as red-black tree)
 *    - Keys are unique and automatically sorted
 *    - O(log n) insertion, deletion, and search
 *    - Similar to Python's OrderedDict (though OrderedDict maintains insertion order, not sorted order)
 * 
 * 3. std::unordered_set - Hash-based set for faster average-case operations
 *    - Uses hash table implementation
 *    - O(1) average case for insertion, deletion, and search
 *    - No guaranteed order of elements
 *    - Similar to Python's set
 * 
 * 4. std::unordered_map - Hash-based key-value container for faster average-case operations
 *    - Uses hash table implementation
 *    - O(1) average case for insertion, deletion, and search
 *    - No guaranteed order of key-value pairs
 *    - Similar to Python's dict (dictionary)
 * 
 * Key Differences between map vs unordered_map:
 * - map: Tree-based (red-black tree), O(log n) operations, sorted by key, ordered iteration
 * - unordered_map: Hash-based, O(1) average operations, no ordering, faster for most use cases
 * 
 * Python Equivalents:
 * - std::set ≈ Python set (but Python set is hash-based like unordered_set)
 * - std::map ≈ Python OrderedDict (maintains order) or sorted dict operations
 * - std::unordered_set ≈ Python set
 * - std::unordered_map ≈ Python dict
 * 
 * The program also demonstrates basic operations like size(), find(), insert(), erase(), and element access.
 */
int main() {

/*     // SET - stores unique elements in sorted order
    std::set<int> numbers = {5, 2, 8, 1, 9, 2}; // duplicate 2 will be ignored
    
    std::cout << "Set contents: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
    
    // MAP - key-value pairs, sorted by key
    std::map<std::string, int> ages;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 22;
    
    std::cout << "Map contents:\n";
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << " years old\n";
    }
    std::cout << "\n";
    
    // UNORDERED_SET - hash-based set for faster operations
    std::unordered_set<std::string> fruits = {"apple", "banana", "orange", "apple"};
    
    std::cout << "Unordered set contents: ";
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << "\n\n";
    
    // UNORDERED_MAP - hash-based map for faster operations
    std::unordered_map<int, std::string> students;
    students[101] = "John";
    students[102] = "Jane";
    students[103] = "Mike";
    
    std::cout << "Unordered map contents:\n";
    for (const auto& student : students) {
        std::cout << "ID " << student.first << ": " << student.second << "\n";
    }
    
    // Demonstrate some operations
    std::cout << "\nOperations:\n";
    std::cout << "Set size: " << numbers.size() << "\n";
    std::cout << "Finding 5 in set: " << (numbers.find(5) != numbers.end() ? "Found" : "Not found") << "\n";
    std::cout << "Alice's age: " << ages["Alice"] << "\n";
    std::set<int> another_set = {3, 4, 5};
    for (const auto& num : another_set) {
        std::pair<std::set<int>::iterator, bool> insert_result = numbers.insert(num);
        numbers.insert(num); // insert elements from another set
        if (insert_result.second) {
            std::cout << "Inserted " << num << " into set.\n";
        } else {
            std::cout << num << " already exists in set.\n";
        }
    } */
    

    std::map<int, std::string> history;
    history[3] = "Implemented a feature";
    history[1] = "Started coding";
    history[20] = "Learned about maps";

    auto latest_it = history.rbegin();
    std::cout << "Latest history entry: " << latest_it->first << ": " << latest_it->second << "\n";
    ++latest_it;
    if (latest_it != history.rend()) {
        std::cout << "Second latest history entry: " << latest_it->first << ": " << latest_it->second << "\n";
    }

    const int n = 5;
    auto it = history.upper_bound(n); //give the first element greater than 5
    if (it != history.end()) {
        std::cout << "Upper bound for " << n << ": " << it->first << ": " << it->second << "\n";
    } else {
        std::cout << "No upper bound found for " << n << "\n";
    }

    auto it2 = history.lower_bound(n);//give the first element not less than 5
    if (it2 != history.end()) {
        std::cout << "Lower bound for " << n << ": " << it2->first << ": " << it2->second << "\n";
    } else {
        std::cout << "No lower bound found for " << n << "\n";
    }

    auto it3 = history.lower_bound(n);
    if (it3 == history.begin()) {
        std::cout << "No element less than " << n << "\n";
    } else {
        --it3;
        std::cout << "Greatest element less than " << n << ": " << it3->first << ": " << it3->second << "\n";
    }
    return 0;
}