/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/06 11:42:00 by jschott          ###   ########.fr       */
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

struct tm	validDate(std::string const &datestring){
	std::string str = datestring;
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	int len = str.length();
//std::cout << "parsing " << str << " of len: " << len << std::endl;
	if (len == 10 
		&& (str[4] != '-' || str[7] != '-' ))
			throw BitcoinExchange::InvalidInputException();
	else if (len == 11 
				&& (str[0] != '-'
				|| str[5] != '-' || str[8] != '-' ))
		throw BitcoinExchange::InvalidInputException();

//std::cout << "mydate: " << datestring.substr(0, len - 6).c_str() << datestring.substr(len - 5, 2).c_str() << datestring.substr(len - 2).c_str() << std::endl;

	struct tm new_date;
	new_date.tm_year = std::atoi(datestring.substr(0, len - 6).c_str()) - 1900;
	if (new_date.tm_year <  0)
		throw BitcoinExchange::InvalidInputDateException();
	
	new_date.tm_mon = std::atoi(datestring.substr(len - 5, 2).c_str()) - 1;
	if (new_date.tm_mon < 0 || new_date.tm_mon > 11)
		throw BitcoinExchange::InvalidInputDateException();	
	new_date.tm_mday = std::atoi(datestring.substr(len - 2).c_str());

//std::cout << "mydate in validDate: " << new_date.tm_year << "-" << new_date.tm_mon << "-"  << new_date.tm_mday << std::endl;// 
	if (new_date.tm_mday > 0 && new_date.tm_mday < 29)
		return (new_date);
	else if (new_date.tm_mday == 29 && (new_date.tm_mon == 1 && !isLeapYear(new_date.tm_year)))
		throw BitcoinExchange::InvalidInputDateException();
	else if (new_date.tm_mday > 31 || (new_date.tm_mday == 31 
				&&	(new_date.tm_mon == 3
					|| new_date.tm_mon == 5 
					|| new_date.tm_mon == 8 
					|| new_date.tm_mon == 10)))
		throw BitcoinExchange::InvalidInputDateException();
	return (new_date);
}

float	validValue(std::string const &valstring){
	float		val;
	char*	error = NULL;

	val = strtof(valstring.c_str(), &error);
	if (*error != '\0')
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

void BitcoinExchange::printDatabase() const {
		std::map<time_t, float>::const_iterator it;
		for (it = _database.begin(); it != _database.end(); ++it) {
			std::cout << date2string(it->first) << ", " << it->second << std::endl;
		}
}

void BitcoinExchange::addValidLine(std::string str, char delimiter) {
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	if (str == "")
		return ;
	if (str.length() < 12)
		throw BitcoinExchange::InvalidInputValueException();
	
	size_t pos = str.find(delimiter);
	if (pos == std::string::npos)
		throw BitcoinExchange::InvalidInputValueException();
	
	try	{
		struct tm new_date_tm = validDate(str.substr(0, pos));
		time_t new_date = mktime(&new_date_tm);
		//std::cout << "mydate converted: " << new_date.tm_year << new_date.tm_mon << new_date.tm_mday << std::endl;// 
		float val = validValue(str.substr(pos + 1));
		std::pair<time_t, float> keyval(new_date, val);
		this->_database.insert(keyval);
	}
	catch(const std::exception& e) {
		std::cerr << COLOR_ERROR <<e.what() << ": " << str << COLOR_STANDARD << std::endl;
	}
}

void	BitcoinExchange::getValidExcangeRate(std::string filename){
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
		throw BitcoinExchange::InvalidInputFile();
	
	std::string line;
	char delimiter;
	try	{
		std::getline(file, line);
		delimiter = findDelimiter(line);
	}
	catch(const std::exception& e){
		std::cerr << COLOR_ERROR <<e.what() << COLOR_STANDARD << std::endl;
	}
	
	std::pair<time_t, float> keyval;
	size_t pos;
	while (std::getline(file, line)){
		try
		{
			pos = line.find(delimiter);
			if (pos == std::string::npos)
			 continue ;
			struct tm new_date_tm = validDate(line.substr(0, pos));
			keyval.first = mktime(&new_date_tm);
			keyval.second  = validValue(line.substr(pos + 1));
			if (keyval.second < 0 || keyval.second > 1000)
				throw BitcoinExchange::InvalidInputValueException();
			std::map<time_t, float>::iterator it = this->_database.find(keyval.first);
			if (it != this->_database.end()){
				std::cout << date2string(keyval.first) << " => " << keyval.second << " * " << it->second <<" =\t" << keyval.second * it->second << std::endl;
			}
			else {
				it = this->_database.upper_bound(keyval.first);
				if (it != this->_database.end()){
					std::cout << date2string(keyval.first) << " => " << keyval.second << " * " << it->second <<" =\t" << keyval.second * it->second << std::endl;
				}
				else
					std::cout << "Having Issues Here" << std::endl;
			}
		}
		catch(const std::exception& e) {
			std::cerr << COLOR_ERROR <<e.what() << ": " << line << COLOR_STANDARD << std::endl;
		}
	}
	file.close();
}

char findDelimiter(std::string &str){
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
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

std::string	 date2string(time_t date){
	struct tm* timeinfo = localtime(&(date));
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	return buffer;
}