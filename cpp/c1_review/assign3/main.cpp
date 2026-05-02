#include "url_history.h"
#include <iostream>

int main() {
    UrlHistory history;
    
    std::cout << "=== URL History Test Program ===" << std::endl;
    
    // Test 1: Add new URLs
    std::cout << "\n1. Adding new URLs:" << std::endl;
    URL url1("https", "www.google.com");
    URL url2("http", "www.example.com");
    URL url3("https", "www.github.com");
    
    history.addUrl(url1);
    history.addUrl(url2);
    history.addUrl(url3);
    
    std::cout << "Added 3 URLs. History size: " << history.size() << std::endl;
    
    // Test 2: Display history
    std::cout << "\n2. Current history (most recent first):" << std::endl;
    const auto& historyList = history.getHistory();
    int index = 1;
    for (const auto& url : historyList) {
        std::cout << index++ << ". " << url.address() << std::endl;
    }
    
    // Test 3: Add duplicate URL (should move to front)
    std::cout << "\n3. Adding duplicate URL (google.com again):" << std::endl;
    history.addUrl(url1);  // Add google.com again
    std::cout << "History size after duplicate: " << history.size() << std::endl;
    
    std::cout << "Updated history:" << std::endl;
    index = 1;
    for (const auto& url : history.getHistory()) {
        std::cout << index++ << ". " << url.address() << std::endl;
    }
    
    // Test 4: Add more URLs
    std::cout << "\n4. Adding more URLs:" << std::endl;
    URL url4("https", "www.stackoverflow.com");
    URL url5("ftp", "files.example.com");
    
    history.addUrl(url4);
    history.addUrl(url5);
    
    std::cout << "Added 2 more URLs. Total size: " << history.size() << std::endl;
    
    // Test 5: Move existing URL to front again
    std::cout << "\n5. Accessing github.com again (should move to front):" << std::endl;
    history.addUrl(url3);  // github.com
    
    std::cout << "Final history:" << std::endl;
    index = 1;
    for (const auto& url : history.getHistory()) {
        std::cout << index++ << ". " << url.address() << std::endl;
    }
    
    // Test 6: Test empty check
    std::cout << "\n6. History empty? " << (history.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Final size: " << history.size() << std::endl;
    
    return 0;
}