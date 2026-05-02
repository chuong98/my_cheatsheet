#include <iostream>
#include "url.h"

int main(){
    URL url("http", "www.alibaba.com");
    std::cout << url.address() << std::endl;
}
