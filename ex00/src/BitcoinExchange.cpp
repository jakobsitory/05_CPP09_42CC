/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/05 17:56:23 by jschott          ###   ########.fr       */
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
	this->_database = origin._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange(){
	
}

time_t	validDate(std::string const &datestring){
	int len = datestring.length();
	if (len == 10 
		&& (datestring[4] != '-' || datestring[7] != '-' ))
			throw BitcoinExchange::InvalidInputException();
	else if (len == 11 
				&& (datestring[0] != '-'
				|| datestring[5] != '-' || datestring[8] != '-' ))
		throw BitcoinExchange::InvalidInputException();

	struct tm new_date;
	new_date.tm_year = std::atoi(datestring.substr(0, len - 6).c_str()) - 1900;
	if (new_date.tm_year ==  -1900 && datestring.substr(0, 4) != "0000" && datestring.substr(0, 5) != "-0000" )
		throw BitcoinExchange::InvalidInputDateException();
	
	new_date.tm_mon = std::atoi(datestring.substr(len - 5, 2).c_str());
	if (new_date.tm_mon < 0 || new_date.tm_mon > 11)
		throw BitcoinExchange::InvalidInputDateException();	
	new_date.tm_mday = std::atoi(datestring.substr(len - 5).c_str());
	if (new_date.tm_mday >= 0 && new_date.tm_mday < 28)
		return mktime(&new_date);
	else if (new_date.tm_mday == 28 && (new_date.tm_mon != 1 || isLeapYear(new_date.tm_year)))
		throw BitcoinExchange::InvalidInputDateException();
	else if (new_date.tm_mday > 30 || (new_date.tm_mday == 30 
				&&	(new_date.tm_mon == 3
					|| new_date.tm_mon == 5 
					|| new_date.tm_mon == 8 
					|| new_date.tm_mon == 10)))
		throw BitcoinExchange::InvalidInputDateException();
	return mktime(&new_date);
}

float	validValue(std::string const &valstring){
	float		val;
	char**	error = NULL;

	val = strtof(valstring.c_str(), error);
	// if (*error != "f")
		// throw BitcoinExchange::InvalidInputValueException();
	if ( val < 0 || val > 1000)
		throw BitcoinExchange::InvalidInputValueException();
	return val;	
}

void	BitcoinExchange::parseDatabase(std::string filename){
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
		throw BitcoinExchange::DatabaseException();
	try	{
		std::string line;
		std::getline(file, line);
		char delimiter = findDelimiter(line);
		while (std::getline(file, line))
			this->addValidLine(line, delimiter);
		file.close();
	}
	catch(const std::exception& e){
		std::cerr << COLOR_ERROR <<e.what() << COLOR_STANDARD << std::endl;
	}
}

void BitcoinExchange::addValidLine(std::string str, char delimiter) {
	std::remove_if(str.begin(), str.end(), isspace);
	if (str == "")
		return ;
	if (str.length() < 12)
		throw BitcoinExchange::InvalidInputValueException();
	
	size_t pos = str.find(delimiter);
	if (pos == std::string::npos)
		throw BitcoinExchange::InvalidInputValueException();
	
	try	{
		time_t new_date = validDate(str.substr(0, pos));
		float val = validValue(str.substr(pos + 1));
		std::pair<time_t, float> keyval(new_date, val);
		this->_database.insert(keyval);
	}
	catch(const std::exception& e) {
		std::cerr << COLOR_ERROR <<e.what() << ": " << str << COLOR_STANDARD << std::endl;
	}
}
char findDelimiter(std::string &str){
	std::remove_if(str.begin(), str.end(), isspace);
	if (str.length() < 6
		|| str.substr(0, 4) != "date")
			throw BitcoinExchange::InvalidInputFormException();
	return str[4];
}

bool isLeapYear(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}
