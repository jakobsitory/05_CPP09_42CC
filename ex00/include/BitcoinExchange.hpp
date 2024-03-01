/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/01 14:58:01 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class BitcoinExchange
{
private:
	/* data */
public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange & origin);
	BitcoinExchange & operator=(BitcoinExchange & origin);
	~BitcoinExchange();
};
