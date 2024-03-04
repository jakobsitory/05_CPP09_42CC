/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/04 12:14:10 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANCE_HPP
# define BITCOINEXCHANCE_HPP

#include <string>
#include <iostream>
#include <iomanip>

class BitcoinExchange
{
private:
	
public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange & origin);
	BitcoinExchange & operator=(BitcoinExchange & origin);
	~BitcoinExchange();

	bool	validDate(std::string &datestring);
	bool	validVal(std::string &valstring);
	void	parseInput(std::string filename);
	
};

#endif