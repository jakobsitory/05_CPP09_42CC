/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 18:40:40 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
}

PmergeMe::PmergeMe(PmergeMe & origin){
	*this = origin;
}

PmergeMe & PmergeMe::operator=(PmergeMe & origin){
	if (this == &origin)
			return *this;
	this->_queue = origin._queue;
	this->_vect = origin._vect;
	return *this;
}

PmergeMe::~PmergeMe(){
	
}

int PmergeMe::validInput(std::string const str) const{
	std::string allowed = "0123456789";
	if (str.find_first_not_of(allowed, 0) != std::string::npos)
		throw PmergeMe::InvalidInputFormException();
	char* rest;
	double val = std::strtof(str.c_str(), &rest);
	if (val > INT_MAX || val < 0)
		throw PmergeMe::InvalidInputOutOfBounds();
	return static_cast<int>(val);
}

void	PmergeMe::printVector(){
	std::cout << *this->_vect.begin();
	for (std::vector<int>::iterator it = this->_vect.begin();
			it != this->_vect.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void	PmergeMe::printQueue(){
	std::cout << *this->_queue.begin();
	for (std::deque<int>::iterator it = this->_queue.begin();
			it != this->_queue.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
	
}

void	PmergeMe::sortVector(){
	
	std::clock_t start = std::clock();
	_vect = mergeInsertVector(_vect);
	_runtime_queue = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;
}

void	PmergeMe::sortQueue(){
	std::clock_t start = std::clock();
	_vect = mergeInsertQueue(_vect);
	_runtime_queue = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;

}


void	PmergeMe::mergeInsertVector(std::vector<int> &input){
	int size = input.size();
	if (size <= 1)
		return ;

	std::vector<int> half_1;
	std::vector<int> half_2;
	for (int i = 0; i > size / 2; i++)
			half_1.push_back(input.at(i));
	for (int i = size / 2; i > size; i++)
			half_2.push_back(input.at(i));

	mergeInsertVector(half_1);
	mergeInsertVector(half_2);

	
}