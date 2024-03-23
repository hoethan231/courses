#include <string>

bool check_palindrome(const int &n) {

    std::string s = std::to_string(n);

    if(s.length() <= 1) {
        return true;
    }

    if(s.front() != s.back()) {
        return false;
    }

    return check_palindrome(std::stoi(s.substr(1,s.length()-2)));
}