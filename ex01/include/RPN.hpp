/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:40 by jschott           #+#    #+#             */
/*   Updated: 2024/03/05 10:15:26 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define _HPP

#define TEXT_NOFORMAT	"\e[0m"
#define TEXT_BOLD		"\e[1m"
#define TEXT_UNDERLINE	"\e[4m"

#define COLOR_STANDARD	"\033[0m"
#define	COLOR_ERROR		"\033[31m"
#define COLOR_WARNING	"\033[33m"
#define COLOR_SUCCESS	"\033[92m"
#define COLOR_FOCUS		"\e[35m"

class RPN
{
private:
	
public:
	RPN();
	RPN(RPN & origin);
	RPN & operator=(RPN & origin);
	~RPN();
};

#endif