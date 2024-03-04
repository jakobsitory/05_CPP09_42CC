/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/04 12:35:21 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){
}

BitcoinExchange::BitcoinExchange(BitcoinExchange & origin){
	*this = origin;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange & origin){
	if (this == &origin)
			return *this;
	//MAKE DEEP COPY
	return *this;
}

BitcoinExchange::~BitcoinExchange(){
	
}

bool	validDate(std::string &datestring){
	if (datestring.length() != 10){
		std::cerr << COLOR_ERROR << "Error: Bad input => " << datestring << COLOR_STANDARD << std::endl;
		return false;
	}
		
			
}

bool	validVal(std::string &valstring){
	float	val;
	char*	error;

	val = strtof(valstring.c_str(), &error);
	if (error != "f"){
		std::cerr << "Error: bad value." << std::endl;
		return false;
	}
	else if ( val < 0){
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	else if (val > 1000){
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;	
}

void	parseInput(std::string filename){
	
}

std::vector<std::string> Btc::splitString(std::string str, char delimiter)
{
	std::vector<std::string> substrings;
	std::string substring = "";
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != delimiter)
		{
			substring += str[i];
		}
		else
		{
			substrings.push_back(substring);
			while (str[i] == delimiter)
				i++;
			i--;
			substring = "";
		}
	}
	substrings.push_back(substring);
	return substrings;
}