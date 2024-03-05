/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/05 17:59:08 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANCE_HPP
# define BITCOINEXCHANCE_HPP

#define TEXT_NOFORMAT	"\e[0m"
#define TEXT_BOLD		"\e[1m"
#define TEXT_UNDERLINE	"\e[4m"

#define COLOR_STANDARD	"\033[0m"
#define	COLOR_ERROR		"\033[31m"
#define COLOR_WARNING	"\033[33m"
#define COLOR_SUCCESS	"\033[92m"
#define COLOR_FOCUS		"\e[35m"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <exception>
#include <algorithm>

class BitcoinExchange
{
private:
	std::map<time_t, float> _database;

public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange & origin);
	BitcoinExchange & operator=(BitcoinExchange & origin);
	~BitcoinExchange();

	void	parseDatabase(std::string filename);
	void	addValidLine(std::string str, char delimiter);
//DEBUGGING REMOVE!	
	void printDatabase() const {
    for (const auto& pair : _database) {
        struct tm* timeinfo = localtime(&pair.first);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        std::cout << buffer << ", " << pair.second << std::endl;
    }
}

	
	class InvalidInputException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Invalid input [YYYY-MM-DD | value]");
				};
	};
	
	class InvalidInputDateException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Invalid date");
				};
	};

	class InvalidInputValueException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Input value out of bounds (0 - 1000)");
				};
	};

	class InvalidInputFormException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Cannot parse input format");
				};
	};

	class DatabaseException : public std::exception{
			public:
				virtual const char* what() const throw(){
					return ("Error: Problems with database");
				};
	};
	
};

// Verify Input Data
char 		findDelimiter(std::string &str);
time_t		validDate(std::string const &datestring);
float		validVal(std::string const &valstring);
bool		isLeapYear(int year);

#endif