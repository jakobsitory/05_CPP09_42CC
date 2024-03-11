/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/11 12:17:13 by jschott          ###   ########.fr       */
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
	int len = str.length();
	if (len == 10 
		&& (str[4] != '-' || str[7] != '-' ))
			throw BitcoinExchange::InvalidInputException();
	else if (len == 11 
				&& (str[0] != '-'
				|| str[5] != '-' || str[8] != '-' ))
		throw BitcoinExchange::InvalidInputException();

	struct tm new_date;
	new_date.tm_hour = 0;
	new_date.tm_min = 0;
	new_date.tm_sec = 0;
	new_date.tm_isdst = -1;
	new_date.tm_year = std::atoi(datestring.substr(0, len - 6).c_str()) - 1900;
	if (new_date.tm_year <  0)
		throw BitcoinExchange::InvalidInputDateException();
	
	new_date.tm_mon = std::atoi(datestring.substr(len - 5, 2).c_str()) - 1;
	if (new_date.tm_mon < 0 || new_date.tm_mon > 11)
		throw BitcoinExchange::InvalidInputDateException();

	new_date.tm_mday = std::atoi(datestring.substr(len - 2).c_str());
	if (new_date.tm_mday < 1 || new_date.tm_mday > 31)
		throw BitcoinExchange::InvalidInputDateException();
    if (new_date.tm_mday == 31 && (new_date.tm_mon == 3 || new_date.tm_mon == 5 || new_date.tm_mon == 8 || new_date.tm_mon == 10))
		throw BitcoinExchange::InvalidInputDateException();
    if (new_date.tm_mon == 1 && ((new_date.tm_mday == 29 && !isLeapYear(new_date.tm_year)) || new_date.tm_mday > 29))
		throw BitcoinExchange::InvalidInputDateException();
	return (new_date);
}

float	validValue(std::string const &valstring){
	float		val;
	char*	error = NULL;

	if (valstring == "")
		throw BitcoinExchange::InvalidInputValueException();
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
		float val = validValue(str.substr(pos + 1));
		std::pair<time_t, float> keyval(new_date, val);
		this->_database.insert(keyval);
	}
	catch(const std::exception& e) {
		std::cerr << COLOR_ERROR <<e.what() << ": " << str << COLOR_STANDARD << std::endl;
	}
}

void valinrange(int val) {
	if (val < 0 || val > 1000)
		throw BitcoinExchange::InvalidInputValueException();
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
		return ;
	}
	
	std::pair<time_t, float> keyval;
	size_t pos;
	std::map<time_t, float>::iterator it;
	std::string datestring;
	std::string valstring; 
	while (std::getline(file, line)){
		if (line == "")
			continue;
		try
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			pos = line.find(delimiter);
			if (pos == std::string::npos)
				throw BitcoinExchange::InvalidInputFormException();
			datestring = line.substr(0, pos);
			valstring = line.substr(pos + 1);
			struct tm new_date_tm = validDate(datestring);
			keyval.first = mktime(&new_date_tm);
			keyval.second  = validValue(valstring);
			time_t now;
			time(&now);
			if (keyval.first < this->_database.begin()->first || keyval.first > now || keyval.first > now)
				throw BitcoinExchange::InvalidInputDateException();
			if (keyval.second < 0 || keyval.second > 1000)
				throw BitcoinExchange::InvalidInputValueException();
			it = this->_database.lower_bound(keyval.first);
			if (it != this->_database.end() && it->first == keyval.first){
				std::cout << date2string(keyval.first) << " => " << keyval.second << " = " << keyval.second * it->second << std::endl;
			}
			else if (it != this->_database.end() && it != this->_database.begin()){
				--it;
				std::cout << date2string(keyval.first) << " => " << keyval.second << " = " << keyval.second * it->second << std::endl;
			}
		}
		catch(const BitcoinExchange::DateExceedsDatabaseException& e) {
			std::cerr << COLOR_ERROR <<e.what() << " of " << _database.begin()->first << " to " << _database.end()->first << ": " << datestring << COLOR_STANDARD << std::endl;
		}
		catch(const BitcoinExchange::InvalidInputValueException& e) {
			std::cerr << COLOR_ERROR <<e.what() << ": " << valstring << COLOR_STANDARD << std::endl;
		}
		catch(const BitcoinExchange::InvalidInputDateException& e) {
			std::cerr << COLOR_ERROR <<e.what() << ": " << datestring << COLOR_STANDARD << std::endl;
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