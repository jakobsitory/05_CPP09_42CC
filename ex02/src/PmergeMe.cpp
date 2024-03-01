/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:54:42 by jschott           #+#    #+#             */
/*   Updated: 2024/03/01 15:04:01 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
}

PmergeMe::PmergeMe(PmergeMe & origin){
	*this = origin;
}

PmergeMe & PmergeMe::operator=(PmergeMe & origin){
	if (this == &origin)
			return *this;
	//MAKE DEEP COPY
	return *this;
}

PmergeMe::~PmergeMe(){
	
}
