#include <iostream>

int recursiveReverseNumber(int n, int reversed = 0) {
    if (n == 0) {
        return reversed;
    }
    
    int lastNum = n % 10;
    int newN = n / 10;
    reversed = (reversed * 10) + lastNum;
    return recursiveReverseNumber(newN, reversed);
}


int main() {
    
    std::cout << recursiveReverseNumber(1234) << std::endl;
    std::cout << recursiveReverseNumber(2468) << std::endl;
    
    return 0;
}