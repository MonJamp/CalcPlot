#include "Calculator.h"

#include <boost/regex.hpp>

#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


Precedence get_precedence(char op) {
	switch(op) {
		case 's':
		case 'm':
			return FUNC;
		case '(':
		case ')':
			return PAREN;
		case '^':
			return EXPO;
		case '*':
		case '/':
		case '%':
			return MUL_DIV;
		case '+':
		case '-':
			return ADD_SUB;
		default:
			return P_UNKNOWN;
	}
}

Associativity get_associativity(char op) {
	switch(op) {
		case '^':
			return RIGHT;
		case '(':
		case ')':
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
			return LEFT;
		default:
			return A_UNKNOWN;
	}
}

Operator::Operator(char op) {
	operation = op;
	order = get_precedence(op);
	assoc = get_associativity(op);
}

int Calc::get_number_length(const std::string number) {
	boost::regex pattern("^(-)?[0-9]+([.][0-9]+)?");
	boost::match_results<std::string::const_iterator> str_matched;
	if(boost::regex_search(number.begin(), number.end(), str_matched, pattern)) {
		int length = str_matched.length();
		
		if(number[length] == '.') {
			return -1;
		}
		
		return length;
	} else {
		return 0;
	}
}

bool is_op(char op) {
	switch(op) {
		case '^':
		case '(':
		case ')':
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
			return true;
		default:
			return false;
	}
}

int is_function(const std::string function) {
	if(function.substr(0, 3) == "sin")
		return 3;
	else if(function.substr(0, 3) == "cos")
		return 3;
	else if(function.substr(0, 3) == "tan")
		return 3;
	else if(function.substr(0, 3) == "max")
		return 3;
	else if(function.substr(0, 3) == "min")
		return 3;
	else
		return 0;
}

std::string Calc::InfixToPostfix(std::string infix) {
	std::vector<std::string> output;
	std::vector<std::string> stack;
	bool last_token_num = false;
	
	for(unsigned int i = 0; i < infix.length(); i++) {
		if(infix[i] == ' ') {
			continue;
		}
		
		int length = get_number_length(infix.substr(i));
		if(length && !last_token_num) {
			last_token_num = true;
			std::string number = infix.substr(i, length);
			output.push_back(number);
			i += length - 1;
		}
		else if((length = is_function(infix.substr(i)))) {
			std::string function = infix.substr(i, length);
			stack.push_back(function);
			i += length - 1;
		}
		else if(infix[i] == 'x') {
			if(last_token_num) {
				infix.insert(i, "*");
				--i;
			} else {
				last_token_num = true;
				output.push_back("x");
			}
		}
		else {
			last_token_num = false;
			char token = infix.c_str()[i];
			
			Operator op(token);
			
			if(op.operation == '(') {
				stack.push_back(std::string(1, op.operation));
			}
			else if(op.operation == ')') {
				while(stack.back() != "(") {
					output.push_back(stack.back());
					stack.pop_back();
				}
				
				stack.pop_back();
			}
			else if(op.operation == ',') {
				while(stack.back() != "(") {
					output.push_back(stack.back());
					stack.pop_back();
				}
			}
			else if(stack.size() > 0) {
				Operator prev_op(stack.back()[0]);
				
				if(prev_op.operation != '(') {
					if(op.assoc == LEFT && op.order <= prev_op.order) {
						output.push_back(stack.back());
						stack.pop_back();
					}
					else if(op.assoc == RIGHT && op.order < prev_op.order) {
						output.push_back(stack.back());
						stack.pop_back();
					}
				}
				
				stack.push_back(std::string(1, op.operation));
			} else {
				stack.push_back(std::string(1, op.operation));
			}
		}
	}
	
	while(stack.size() > 0) {
		output.push_back(stack.back());
		stack.pop_back();
	}
	
	std::stringstream postfix;
	for(auto x : output) {
		postfix << x << " ";
	}
	
	return postfix.str();
}

inline double solve(double num1, double num2, char op) {
	switch(op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			return num1 / num2;
		case '%':
			return std::fmod(num1, num2);
		case '^':
			return std::pow(num1, num2);
		default:
			return 0;
	}
}

int get_arg_count(std::string func) {
	if(func == "sin" || func == "cos" || func == "tan")
		return 1;
	else if(func == "max" || func == "min")
		return 2;
	else
		return 0;
}

inline double solve(std::string func, double num1, double num2 = 0) {
	if(func == "sin")
		return std::sin(num1);
	else if(func == "cos")
		return std::cos(num1);
	else if(func == "tan")
		return std::tan(num1);
	else if(func == "max")
		return std::max(num1, num2);
	else if(func == "min")
		return std::min(num1, num2);
	else
		return 0;
}

//For testing
double Calc::infix(std::string infix) {
	std::string postfix = Calc::InfixToPostfix(infix);
	return Calc::postfix(postfix);
}

double Calc::postfix(std::string postfix) {
	std::vector<double> stack;
	
	for(unsigned int i = 0; i < postfix.length(); i++) {
		if(postfix[i] == ' ') {
			continue;
		}
		
		int num_length = get_number_length(postfix.substr(i));
		
		if(num_length > 0) {
			double number = std::stod(postfix.substr(i, num_length));
			stack.push_back(number);
			i += num_length - 1;
		} else {
			double num1, num2;
			double result;
			std::string op;
			
			if((num_length = is_function(postfix.substr(i)))) {
				op = postfix.substr(i, num_length);
				i += num_length - 1;
				
				int argc = get_arg_count(op);
				
				num1 = stack.back();
				stack.pop_back();
				
				if(argc == 1)
					result = solve(op, num1);
				else if(argc == 2) {
					num2 = stack.back();
					stack.pop_back();
					result = solve(op, num1, num2);
				}
			} else {
				num2 = stack.back();
				stack.pop_back();
				num1 = stack.back();
				stack.pop_back();
				
				op = postfix.substr(i , 1);
				result = solve(num1, num2, op[0]);
			}
			
			stack.push_back(result);
		}
	}
	return stack.back();
}

std::vector<double> Calc::InfixToPoints(std::string infix, double min, double max, double inc) {
	std::vector<double> points;
	std::vector<unsigned int> index;
	std::string postfix = Calc::InfixToPostfix(infix);
	
	for(unsigned int i = 0; i < postfix.length(); i++) {
		if(postfix[i] == 'x') {
			index.push_back(i);
		}
	}
	
	for(double i = min; i <= max; i += inc) {
		std::string n_postfix = postfix;
		for(unsigned int j = 0; j < index.size(); ++j) {
			unsigned int k = index.back();
			n_postfix.erase(k, 1);
			n_postfix.insert(k, std::to_string(i));
		}
		
		points.push_back(i); // x
		points.push_back(Calc::postfix(n_postfix)); // y
	}
	
	return points;
}