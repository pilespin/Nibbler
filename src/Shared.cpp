/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/11 18:03:41 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shared.hpp"

Shared::Shared() 						{	this->_val = 0;	}
Shared::Shared(int sizeX, int sizeY) : mapSizeX(sizeX), mapSizeY(sizeY)	{
	std::cout << "sizeX: " << sizeX << std::endl;
	std::cout << "sizeY: " << sizeY << std::endl;

	this->map = new int*[sizeY];
	int i = -1;
	while (++i < sizeY)
	{
		std::cout << "I: " << i << std::endl;
		this->map[i] = new int[sizeX];
	}
    	//////////////////////////////////debug//////
	// std::cout << "----------------------" << std::endl;
	// i = -1;
	// while (++i < sizeY)
	// {
	// 	int j = -1;
	// 	while (++j < sizeX)
	// 		this->map[i][j] = 0;
	// }
	// std::cout << "----------------------" << std::endl;
    	//////////////////////////////////debug//////
}

Shared::~Shared()						{}

Shared::Shared(Shared const &src)	{	*this = src;	}

Shared	&Shared::operator=(Shared const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Shared &c) {
	o << "Shared: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Shared::getValue() const	{	return (this->_val);	}
void	Shared::setCommand(eCommand command) {
	this->command = command;
}

///////////////////////////////////////////////////////////////////////////////
void	Shared::empty() {

}
