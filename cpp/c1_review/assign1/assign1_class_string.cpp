#include <iostream>
#include <string>

/* write a class that represent URL, eg. https://www.amazon.com
It has 2 members of type std: string
- protocol, e.g http
- resource, e.g www.amazon.com
- constructor that takes protocol and resource as arguments
- member function which return complete URL
*/
class URL{
    private:
        std::string protocol;
        std::string resource;

    public:
        // Constructor
        URL(const std::string protocol, const std::string resource): protocol(protocol), resource(resource){}
        std::string address(){
            return protocol + "://" + resource;
        }
};

int main(){
    URL url("http", "www.alibaba.com");
    std::cout << url.address() << std::endl;
}