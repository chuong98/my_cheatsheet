#ifndef URL_H
#define URL_H

#include <string>

// In C++ header files, you need to put a semicolon (;) at the end of function declarations,
// but NOT at the end of function definitions.

class URL{
    private:
        std::string protocol;
        std::string resource;
    public:
        // Constructor
        URL(const std::string& protocol, const std::string& resource);
        
        // Getters (const methods)
        std::string getProtocol() const;
        std::string getResource() const;
        std::string address() const;
        
        // Setters
        void setProtocol(const std::string& protocol);
        void setResource(const std::string& resource);
        
        // Default constructor (optional)
        URL() = default;
        
        // Copy constructor and assignment operator (optional - compiler generates them)
        // URL(const URL& other) = default;
        // URL& operator=(const URL& other) = default;
        bool operator==(const URL& other) const {
            return protocol == other.protocol && resource == other.resource;
        }

        bool operator!=(const URL& other) const {
            return !(*this == other);
        }
};

#endif