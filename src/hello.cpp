//# is slightly similar to import
//# is call a preprocessor, finds stuff and brings it in to the compiler
//g++ -std=c++11 -c hello.cpp ----compile step
//g++ -std=c++11 -o hello hello.o
//
#include <iostream>

int main() {
    std::cout << "Hello, world." << std::endl;
    return 0;
}