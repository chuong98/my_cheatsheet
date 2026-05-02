#include "url.h"

// Constructor
URL::URL(const std::string& protocol, const std::string& resource) 
    : protocol(protocol), resource(resource) {}

// Getters
std::string URL::getProtocol() const {
    return protocol;
}

std::string URL::getResource() const {
    return resource;
}

std::string URL::address() const {
    return protocol + "://" + resource;
}

// Setters
void URL::setProtocol(const std::string& protocol) {
    this->protocol = protocol;
}

void URL::setResource(const std::string& resource) {
    this->resource = resource;
}