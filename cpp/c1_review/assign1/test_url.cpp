#include <iostream>
#include "url.h"

int main() {
    // Test original functionality
    URL url1("https", "www.google.com");
    std::cout << "URL 1: " << url1.address() << std::endl;
    
    // Test getters
    std::cout << "Protocol: " << url1.getProtocol() << std::endl;
    std::cout << "Resource: " << url1.getResource() << std::endl;
    
    // Test setters
    url1.setProtocol("ftp");
    url1.setResource("files.example.com");
    std::cout << "Modified URL: " << url1.address() << std::endl;
    
    // Test default constructor
    URL url2;
    url2.setProtocol("http");
    url2.setResource("localhost:8080");
    std::cout << "URL 2: " << url2.address() << std::endl;
    
    return 0;
}
