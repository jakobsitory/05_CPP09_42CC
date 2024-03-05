/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:53 by jschott           #+#    #+#             */
/*   Updated: 2024/03/05 17:59:47 by jschott          ###   ########.fr       */
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
	btc.parseDatabase("input/data.csv");
	btc.printDatabase();

	std::cout << argv[1] << std::endl;
	return 0;
}