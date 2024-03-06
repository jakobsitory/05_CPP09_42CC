/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:53 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 17:06:48 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main (int argc, char **argv){

	if (argc != 2){
		std::cerr << COLOR_ERROR << "Error: invalid argument" << COLOR_ERROR << std::endl;
		return 1;
	}
	if (strlen(argv[1]) == 1 && isdigit(argv[1][0]))
		std::cout << TEXT_BOLD <<  (argv[1]) << TEXT_NOFORMAT <<  std::endl;
	
	else {
		try {
			RPN rpn;
			rpn.validInput(argv[1]);
			int result = rpn.sequenceRPN(argv[1]);
			std::cout << TEXT_BOLD << result << TEXT_BOLD << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << COLOR_ERROR  << e.what() << COLOR_ERROR << std::endl;
		}
	}
	return 0;
}