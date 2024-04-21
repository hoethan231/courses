#include <iostream>
#include <stack>
#include <string>

std::string expressionToPostfix(std::string s) {

    std::string output = "";
    std::stack<std::string> myStack;
    myStack.push("");

    for(int i=0; i<s.length(); i++) {
        std::string Char = s.substr(i,1);
        
        if(Char == ";") {
            break;
        }
        else if(Char == "(") {
            myStack.push(Char);
        }
        else if(Char == ")") {
            while(!myStack.empty() && myStack.top() != "(") {
                output += myStack.top();
                myStack.pop();
            }
            myStack.pop();
        }
        else if(Char == "+" || Char == "-" || Char == "*" || Char == "/") {
            while(!myStack.empty() && myStack.top() != "(") {
                if(Char == myStack.top()) {
                    myStack.push(Char);
                }
                else if(myStack.top() == "*" || myStack.top() == "/") {
                    output += myStack.top();
                    myStack.pop();
                }
                else {
                    myStack.push(Char);
                    break;
                }
            }
            if(myStack.top() == "(") {
                myStack.push(Char);
            }
        }
        else {
            output += Char;
        }
    }
    while(!myStack.empty()) {
        output += myStack.top();
        myStack.pop();
    }

    return output;
}

double evaluatePostFix(std::string expression) {

    std::stack<std::string> myStack;

    for(int i=0; i<expression.length(); i++) {
        std::string Char = expression.substr(i,1);

        if(Char == "+" || Char == "-" || Char == "*" || Char == "/") {
            double result = std::stod(myStack.top());
            myStack.pop();
            switch(Char[0]) {
                case '*':
                    result *= std::stod(myStack.top());
                    break;
                case '/':
                    result /= std::stod(myStack.top());
                    break;
                case '+':
                    result += std::stod(myStack.top());
                    break;
                case '-':
                    result -= std::stod(myStack.top());
                    break;
            }
            myStack.pop();
            myStack.push(std::to_string(result));
        }
        else {
            myStack.push(Char);
        }
    }
    return std::stod(myStack.top());
}

int main() {
    
    std::cout << std::endl;

    std::string s = "A+B*C";
    std::string expected = "ABC*+";
    std::cout << s << " to postfix is: " << expressionToPostfix(s) << " and expected: " << (expressionToPostfix(s) == expected) << std::endl;
    
    std::string s1 = "(A+B)*C";
    std::string expected1 = "AB+C*";
    std::cout << s1 << " to postfix is: " << expressionToPostfix(s1) << " and expected: " << (expressionToPostfix(s1) == expected1) << std::endl;
    
    std::string s2 = "A*B+C";
    std::string expected2 = "AB*C+";
    std::cout << s2 << " to postfix is: " << expressionToPostfix(s2) << " and expected: " << (expressionToPostfix(s2) == expected2) << std::endl;
    
    std::string s3 = expressionToPostfix("(5+5)*2");
    std::cout << evaluatePostFix(s3) << std::endl;

    std::string s4 = expressionToPostfix("5*5+2");
    std::cout << evaluatePostFix(s4) << std::endl;

    return 0;
}