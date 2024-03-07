/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:53 by jschott           #+#    #+#             */
/*   Updated: 2024/03/07 10:35:48 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int argc, char** argv){
	
	if (argc < 2){
		std::cerr << COLOR_ERROR << "Error: Invalid input" << COLOR_ERROR << std::endl;
		return 1;
	}
	try	{
		PmergeMe pmm;
		for (int i = 1; i < argc; i++) {
			std::string input = argv[i];
			int val = pmm.validInput(input);		
			pmm._vect.push_back(val);
			pmm._queue.push_back(val);
		}
		std::cout << TEXT_BOLD << "Before:" << TEXT_NOFORMAT << std::endl;
		//std::cout << COLOR_WARNING << "std::deque" << std::endl;
		pmm.printQueue();
		//std::cout << COLOR_FOCUS << "std::vector" << std::endl;
		//pmm.printVector();

		pmm.sortVector();
		pmm.sortQueue();
		
		std::cout << COLOR_STANDARD << TEXT_BOLD << std::endl << "After:"  << TEXT_NOFORMAT << std::endl,
		//std::cout << COLOR_WARNING << "std::deque" << std::endl;
		pmm.printQueue();
		//std::cout << COLOR_FOCUS << "std::vector" << std::endl;
		//pmm.printVector();

		std::cout << std::endl;
		std::cout << COLOR_WARNING << "Time to process a range of " << argc - 1 << " elements with std::Deque:  " << pmm._runtime_queue << " μs" << std::endl;
		std::cout << COLOR_FOCUS << "Time to process a range of " << argc - 1 << " elements with std::Vector: " << pmm._runtime_vect << " μs" <<  std::endl;

		// COUNT OUTPUT & CHECK SORT
		//std::cout << COLOR_WARNING  << TEXT_BOLD << "std::Deque ->  "<< pmm._queue.size() << " elements "<< pmm.isSortedQueue()  << std::endl;
		//std::cout << COLOR_FOCUS  << TEXT_BOLD << "std::Vector -> " << pmm._vect.size() << " elements " << pmm.isSortedVector()  << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << COLOR_ERROR << e.what() << COLOR_ERROR << std::endl;
	}
	
	
	return 0;
}