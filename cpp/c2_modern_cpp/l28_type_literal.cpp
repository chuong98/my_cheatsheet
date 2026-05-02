#include <iostream>
#include <string>

int main() {
    // Regular string with escape sequences
    std::string regular = "This is a \"quoted\" string with a newline:\nAnd a tab:\t";
    
    // Raw string literal - no need to escape characters
    std::string raw = R"(This is a "quoted" string with a newline:
And a tab:	)";
    
    // Raw string with custom delimiter, delim( or x( 
    // If you used a basic raw string R"(...)", the parser would incorrectly think the string ends at the first )" it encounters inside the content. 
    // By using delim, the parser only ends the string when it finds )delim".
    std::string rawWithDelimiter = R"x(
    This string can contain )" without issues
    because we use a custom delimiter: x
    )x";
    
    // Useful for file paths on Windows
    std::string path = R"(C:\Users\Documents\file.txt)";
    
    // Useful for regex patterns
    std::string regex = R"(\d{3}-\d{3}-\d{4})";
    
    std::cout << "Regular: " << regular << std::endl;
    std::cout << "Raw: " << raw << std::endl;
    std::cout << "Raw with delimiter: " << rawWithDelimiter << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Regex: " << regex << std::endl;
    
    return 0;
}