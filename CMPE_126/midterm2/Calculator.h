#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include <stack>
#include <string>

class Calculator {
public:
	Calculator();
	~Calculator();
	void add(double);
	void subtract(double);
	double getResult();
	void undo();
	void redo();
	void printAllOperations();
private:
	double result;
	std::stack<double> undoStack;
	std::stack<double> redoStack;
	std::stack<std::string> operationsStack;
	/*****************
	 * Add any fields you need
	 *****************/
};

#endif /* CALCULATOR_H_ */
