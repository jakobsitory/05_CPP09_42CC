/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/07 10:28:48 by jschott          ###   ########.fr       */
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
	this->_runtime_queue = origin._runtime_queue;
	this->_runtime_vect = origin._runtime_vect;
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
	std::cout << this->_vect.front();
	for (std::vector<int>::iterator it = this->_vect.begin() + 1;
			it != this->_vect.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

std::vector<int>	PmergeMe::mergeVector(std::vector<int> &input_1, std::vector<int> &input_2){
	std::vector<int> mergedVector;

	while (!input_1.empty() && !input_2.empty()){
		if (input_1.front() <= input_2.front()){
			mergedVector.push_back(input_1.front());
			input_1.erase(input_1.begin());
		}
		else{
			mergedVector.push_back(input_2.front());
			input_2.erase(input_2.begin());
		}
	}
	while (!input_1.empty()){
		mergedVector.push_back(input_1.front());
		input_1.erase(input_1.begin());
	}
	while (!input_2.empty()){
		mergedVector.push_back(input_2.front());
		input_2.erase(input_2.begin());
	}

	return (mergedVector);
}

std::vector<int>	PmergeMe::mergeInsertVector(std::vector<int> &input){
	int size = input.size();
	if (size <= 1)
		return input;
	size /= 2;
	std::vector<int> half_1(input.begin(), input.begin() + size );
	std::vector<int> half_2(input.begin() + size, input.end());

	half_1 = mergeInsertVector(half_1);
	half_2 = mergeInsertVector(half_2);

	return (mergeVector(half_1, half_2));
}

void	PmergeMe::sortVector(){
	
	std::clock_t start = std::clock();
	_vect = mergeInsertVector(_vect);
	_runtime_vect = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;
}

std::string		PmergeMe::isSortedVector(){
	for (std::vector<int>::const_iterator it = _vect.begin();
			it != _vect.end() - 1; ++it) {
		if (*it > *(it + 1)) {
			return "not sorted";
		}
	}
	return "sorted";
}

void	PmergeMe::printQueue(){
	std::cout << this->_queue.front();
	for (std::deque<int>::iterator it = this->_queue.begin() + 1;
			it != this->_queue.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
	
}

std::deque<int> PmergeMe::mergeQueue(std::deque<int> &input_1, std::deque<int> &input_2){
	std::deque<int> mergedQueue;

	while (!input_1.empty() && !input_2.empty()){
		if (input_1.front() <= input_2.front()){
			mergedQueue.push_back(input_1.front());
			input_1.erase(input_1.begin());
		}
		else{
			mergedQueue.push_back(input_2.front());
			input_2.erase(input_2.begin());
		}
	}
	while (!input_1.empty()){
		mergedQueue.push_back(input_1.front());
		input_1.erase(input_1.begin());
	}
	while (!input_2.empty()){
		mergedQueue.push_back(input_2.front());
		input_2.erase(input_2.begin());
	}

	return (mergedQueue);
}

std::deque<int>	PmergeMe::mergeInsertQueue(std::deque<int> &input){
	int size = input.size();
	if (size <= 1)
		return input;
	size /= 2;
	std::deque<int> half_1(input.begin(), input.begin() + size);
	std::deque<int> half_2(input.begin() + size, input.end());

	half_1 = mergeInsertQueue(half_1);
	half_2 = mergeInsertQueue(half_2);

	return (mergeQueue(half_1, half_2));
}

void	PmergeMe::sortQueue(){
	std::clock_t start = std::clock();
	_queue = mergeInsertQueue(_queue);
	_runtime_queue = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MICROSECOND;

}
std::string		PmergeMe::isSortedQueue(){
	for (std::deque<int>::const_iterator it = _queue.begin();
			it != _queue.end() - 1; ++it) {
        if (*it > *(it + 1)) {
            return "not sorted";
        }
    }
	return "sorted";
}