/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/10 19:28:21 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shared.hpp"

Shared::Shared() 						{	this->_val = 0;	}

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
int		Shared::getX() const		{	return (this->x);	}
int		Shared::getY() const		{	return (this->y);	}
void	Shared::setCommand(eCommand command) {
	// mutex.lock();
	this->command = command;
	// mutex.unlock();
}

void	Shared::setX(int x) {
	// mutex.lock();
	this->x = x;
	// mutex.unlock();
}

void	Shared::setY(int y) {
	// mutex.lock();
	this->y = y;
	// mutex.unlock();
}

///////////////////////////////////////////////////////////////////////////////
void	Shared::empty() {

}
