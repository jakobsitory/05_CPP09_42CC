/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:53 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 18:18:33 by jschott          ###   ########.fr       */
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
		std::cout << "Before:\t",
		pmm.printQueue();
		//pmm.printVector();

		pmm.sortVector();
		pmm.sortQueue();
		
		std::cout << "After:\t",
		pmm.printQueue();
		//pmm.printVector();

		std::cout << "Time to process a range of 3000 elements with std::Deque :  " << pmm._runtime_queue;
		std::cout << "Time to process a range of 3000 elements with std::Vector : " << pmm._runtime_vect;
	}
	catch(const std::exception& e) {
		std::cerr << COLOR_ERROR << e.what() << COLOR_ERROR << std::endl;
	}
	
	
	return 0;
}