/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:40 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 16:57:12 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define _HPP

#define TEXT_NOFORMAT	"\e[0m"
#define TEXT_BOLD		"\e[1m"
#define TEXT_UNDERLINE	"\e[4m"

#define COLOR_STANDARD	"\033[0m"
#define	COLOR_ERROR		"\033[31m"
#define COLOR_WARNING	"\033[33m"
#define COLOR_SUCCESS	"\033[92m"
#define COLOR_FOCUS		"\e[35m"

#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <cstdlib>

class RPN
{
private:
    std::stack<int> 	_vals;

	std::string	const	_digits;
	std::string	const	_operations;
public:
	RPN();
	RPN(RPN & origin);
	RPN & operator=(RPN & origin);
	~RPN();
	

	bool	validInput(std::string const str) const;
	void	calculate(int num_l, int num_r, char op);
	int		sequenceRPN(std::string const str);

	class InvalidInputFormException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Invalid input");
				};
	};
	class InvalidOperation : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Invalid Operation");
				};
	};
};

#endif