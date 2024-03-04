/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:26:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/04 10:29:36 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Date
{
private:
	int _year;
	int _month;
	int _day;

public:
	Date(/* args */);
	Date(char* datestring);
	Date(Date & origin);
	Date& operator=(Date & origin);
	~Date();

	int getYear();
	int getMonth();
	int getDay();
};

