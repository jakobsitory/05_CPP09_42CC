/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/01 15:03:33 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#define TEXT_NOFORMAT	"\e[0m"
#define TEXT_BOLD		"\e[1m"
#define TEXT_UNDERLINE	"\e[4m"

#define COLOR_STANDARD	"\033[0m"
#define	COLOR_ERROR		"\033[31m"
#define COLOR_WARNING	"\033[33m"
#define COLOR_SUCCESS	"\033[92m"
#define COLOR_FOCUS		"\e[35m"

# define NANOSECOND		100000000
# define MICROSECOND	100000
# define MILLISECOND	100

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class PmergeMe
{
private:
public:
	std::deque<int>		_queue;
	std::vector<int>	_vect;
	double				_runtime_queue;
	double				_runtime_vect;

	PmergeMe();
	PmergeMe(PmergeMe & origin);
	PmergeMe & operator=(PmergeMe & origin);
	~PmergeMe();

	int		validInput(std::string const str) const;
	
	//Vector Ops
	void				printVector();
	std::vector<int>	mergeVector(std::vector<int> &input_1, std::vector<int> &input_2);
	std::vector<int>	mergeInsertVector(std::vector<int> &input);
	void				sortVector();
	std::string			isSortedVector();

	//Deque Ops
	void			printQueue();
	std::deque<int> mergeQueue(std::deque<int> &input_1, std::deque<int> &input_2);
	std::deque<int>	mergeInsertQueue(std::deque<int> &input);
	void			sortQueue();
	std::string		isSortedQueue();

	class InvalidInputFormException : public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Invalid input");
			};
	};
	
	class InvalidInputOutOfBounds : public std::exception{
		public:
			virtual const char* what() const throw(){
				return ("Error: Input out of bounds");
			};
	};
};

#endif