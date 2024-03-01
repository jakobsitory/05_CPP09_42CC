/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:00:25 by jschott           #+#    #+#             */
/*   Updated: 2024/03/01 15:01:22 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){
	
}

RPN::RPN(RPN & origin){
	*this = origin;
}

RPN & RPN::operator=(RPN & origin){
	if (this == &origin)
			return *this;
	//MAKE DEEP COPY
	return *this;
}

RPN::~RPN(){
	
}
