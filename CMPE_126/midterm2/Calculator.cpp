#include <iostream>
#include "Calculator.h"

Calculator::Calculator() : result(0) {}

Calculator::~Calculator() {
    result = 0;
    while(!undoStack.empty()) {
        undoStack.pop();
    }
    while(!redoStack.empty()) {
        undoStack.pop();
    }
}

void Calculator::add(double n) {
    result += n;
    undoStack.push(n);
    operationsStack.push("Add " + std::to_string(n) + " ");
}

void Calculator::subtract(double n) {
    result -= n;
    undoStack.push(-n);
    operationsStack.push("Subtract " + std::to_string(n) + " ");
}

double Calculator::getResult() {
    return result;
}

void Calculator::undo() {

    if(undoStack.empty()) {
        std::cout << "No undo operation possible" << std::endl;
    }

    result -= undoStack.top();
    redoStack.push(undoStack.top());
    undoStack.pop();
    operationsStack.push("Undo ");
}

void Calculator::redo() {

    if(redoStack.empty()) { 
        std::cout << "No redo operation possible" << std::endl;
    }

    result += redoStack.top();
    undoStack.push(redoStack.top());
    redoStack.pop();
    operationsStack.push("Redo ");
}

void Calculator::printAllOperations() {
    std::string output = "";

    while(!operationsStack.empty()) {
        output = operationsStack.top() + output + " ";
        operationsStack.pop();
    }

    std::cout << output << std::endl;
}