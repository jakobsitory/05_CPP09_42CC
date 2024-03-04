/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/04 10:22:58 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class BitcoinExchange
{
private:
	int
public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange & origin);
	BitcoinExchange & operator=(BitcoinExchange & origin);
	~BitcoinExchange();
};
