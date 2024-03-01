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
