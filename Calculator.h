#pragma once

#include <string>
#include <vector>


enum Precedence {
	P_UNKNOWN,
	ADD_SUB,
	MUL_DIV,
	EXPO,
	PAREN,
	FUNC
};

enum Associativity {
	A_UNKNOWN,
	LEFT,
	RIGHT
};

struct Operator {
	Operator(char op);
	char operation;
	Precedence order;
	Associativity assoc;
};

namespace Calc {
	int get_number_length(std::string number);
	double infix(std::string infix);
	double postfix(std::string postfix);
	std::string InfixToPostfix(std::string infix);
	std::vector<double> InfixToPoints(std::string infix, double min, double max, double inc);
};
