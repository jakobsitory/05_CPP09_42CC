/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:34 by jschott           #+#    #+#             */
/*   Updated: 2024/03/01 15:03:33 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#define TEXT_NOFORMAT	"\e[0m"
#define TEXT_BOLD		"\e[1m"
#define TEXT_UNDERLINE	"\e[4m"

#define COLOR_STANDARD	"\033[0m"
#define	COLOR_ERROR		"\033[31m"
#define COLOR_WARNING	"\033[33m"
#define COLOR_SUCCESS	"\033[92m"
#define COLOR_FOCUS		"\e[35m"

class PmergeMe
{
private:
	/* data */
public:
	PmergeMe();
	PmergeMe(PmergeMe & origin);
	PmergeMe & operator=(PmergeMe & origin);
	~PmergeMe();
};

#endif