#include <iostream>
#include <vector>
#include <map>
#include <string>

/* Write a program that reads words from input.

Store the value and length of each word in a suitable std::pair.
Store each pair in
- A vector
- A map whose key and value have the appropriate types

Print out all the elements of the vector and the map. 
*/
int main(){
    std::vector<std::pair<std::string, int>> wordVector;
    std::map<std::string, int> wordMap;
    
    std::string input;
    std::cout << "Enter words (type 'quit' to stop):" << std::endl;
    
    while(std::cin >> input && input != "quit") {
        // check if special character in input such as , . " and remove it
        input.erase(std::remove_if(input.begin(), input.end(), 
            [](char c) { return c == ',' || c == '.' || c == '"' || c == '?'; }), input.end());
        std::pair<std::string, int> word = std::make_pair(input, input.length());
        wordVector.push_back(word);
        wordMap[input] = input.length();
    }
    
    std::cout << "\nVector contents:" << std::endl;
    for(const auto& pair : wordVector) {
        std::cout << "Word: " << pair.first << ", Length: " << pair.second << std::endl;
    }
    
    std::cout << "\nMap contents:" << std::endl;
    for(const auto& pair : wordMap) {
        std::cout << "Word: " << pair.first << ", Length: " << pair.second << std::endl;
    }
    
    return 0;
}