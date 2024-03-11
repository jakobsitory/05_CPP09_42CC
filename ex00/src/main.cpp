/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:53 by jschott           #+#    #+#             */
/*   Updated: 2024/03/11 11:52:05 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

int main (int argc, char** argv){

	if (argc != 2){
		std::cerr << COLOR_ERROR << "Error: invalid input" << COLOR_STANDARD << std::endl;
		return (1);
	}
	BitcoinExchange btc;
	try	{
		btc.parseDatabase("input/data.csv");
		btc.getValidExcangeRate(argv[1]);
	}
	catch(const std::exception& e){
		std::cerr << COLOR_ERROR <<e.what() << COLOR_STANDARD << std::endl;
		return (1);
	}
	return 0;
}