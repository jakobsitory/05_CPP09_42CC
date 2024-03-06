/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:00:25 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 17:04:29 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(): _digits("0123456789"), _operations("+-*/"){
}

RPN::RPN(RPN & origin){
	*this = origin;
}

RPN & RPN::operator=(RPN & origin){
	if (this == &origin)
			return *this;
	this->_vals = origin._vals;
	return *this;
}

RPN::~RPN(){
}

bool RPN::validInput(std::string const str) const{
	std::string allowed = this->_digits + this->_operations;
	int len = str.length();
	for (int i = 0; i < len; i++){
		if (i % 2 == 0 && allowed.find(str[i]) == std::string::npos)
			throw RPN::InvalidInputFormException();
		else if (i % 2 == 1 && !isspace(str[i]))
			throw RPN::InvalidInputFormException();
	}
	return true;
}

int RPN::sequenceRPN(std::string const str) {
	std::string	op;
	int len = str.length();
	
	for (int i = 0; i < len; i++){
		if (isspace(str[i]))
			continue ;
		else if (isdigit(str[i]))
			op += str[i];
		else if (this->_operations.find(str[i]) != std::string::npos) {
			if (this->_vals.size() < 2)
				throw RPN::InvalidInputFormException();
			int num_r = this->_vals.top();
			this->_vals.pop();
			int num_l = this->_vals.top();
			this->_vals.pop();
			calculate(num_l, num_r, str[i]);
			continue ;
		}
		else
			throw RPN::InvalidInputFormException();
		if (!op.empty())
		{
			this->_vals.push(std::atoi(op.c_str()));
			op.clear();
		}
	}
	if (this->_vals.size() != 1)
		throw RPN::InvalidInputFormException();
	int result = this->_vals.top();
	this->_vals.pop();
	return result;
}

void	RPN::calculate(int num_l, int num_r, char op) {
	if (this->_operations.find(op) == std::string::npos)
		throw RPN::InvalidOperation();
	switch (op)
	{
		case '+':
			this->_vals.push(num_l + num_r);
			break;
		case '-':
			this->_vals.push(num_l - num_r);
			break;
		case '*':
			this->_vals.push(num_l * num_r);
			break;
		case '/':
			if (num_r == 0)
				throw RPN::InvalidOperation();
			this->_vals.push(num_l / num_r);
			break;
	}
}