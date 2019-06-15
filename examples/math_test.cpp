#include <iostream>
#include <sstream>

#include <cmath>

int main(const int argc, const char * const * const argv) {
    // std::cout << "(4*10)/3 = " << (4*10)/3 << std::endl;
    // std::cout << "std::ceil((4*10)/3) = " << std::ceil((4*10)/3) << std::endl;
    
    // std::cout << "(4*10)/3.0 = " << (4*10)/3.0 << std::endl;
    // std::cout << "std::ceil((4*10)/3.0) = " << std::ceil((4*10)/3.0) << std::endl;
    // std::cout << "std::ceil((4*10)/3.0) + 4 - ((int)std::ceil((4*10)/3.0) % 4) = " << std::ceil((4*10)/3.0) + 4 - ((int)std::ceil((4*10)/3.0) % 4) << std::endl;

    // std::cout << std::endl;

    unsigned int n = 10;

    if(2 == argc){
        n = std::atoi(argv[1]);
    }

    size_t lB64Length = std::ceil((4*n)/3.0);
    lB64Length = lB64Length + 4 - (lB64Length % 4);

    std::cout << "size_t lB64Length = std::ceil((4*" << n << ")/3.0);" << std::endl;
    std::cout << "lB64Length = lB64Length + 4 - (lB64Length % 4);" << std::endl;
    std::cout << "lB64Length = " << lB64Length << std::endl;
}