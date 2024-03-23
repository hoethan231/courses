#include <iostream>

unsigned int padovan(const unsigned int &n) {

    if(n == 0 || n == 1 || n == 2) {
        return 1;
    }

    return padovan(n - 2) + padovan(n - 3);

}

unsigned int padovanWithSteps(const unsigned int &n) {

    if(n == 0 || n == 1 || n == 2) {
        std::cout << "Returning 1 with n = " << n << std::endl;
        return 1;
    }

    std::cout << "In padovan with n = " << n << std::endl;
    return padovanWithSteps(n - 2) + padovanWithSteps(n - 3);

}