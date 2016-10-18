/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:09:43 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Shared.hpp"
#include "Object.hpp"

Shared::Shared() 						{	
	this->_val = 0;
}

Shared::Shared(int sizeX, int sizeY) : mapSizeX(sizeX), mapSizeY(sizeY)	{

	this->lib = eChoseLib::Lib1;

	this->map = new int*[sizeY];
	int i = -1;
	while (++i < sizeY)
	{
		this->map[i] = new int[sizeX];
		int j = -1;
		while (++j < sizeX)
			this->map[i][j] = 0;
	}
}

Shared::~Shared()						{}

Shared::Shared(Shared const &src)	{	

	this->_val = src._val;
	this->command = src.command;
	this->lastCommand = src.lastCommand;
	this->mapSizeX = src.mapSizeX;
	this->mapSizeY = src.mapSizeY;
	// *this = src;
}

Shared	&Shared::operator=(Shared const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
		this->command = rhs.command;
		this->lastCommand = rhs.lastCommand;
		this->mapSizeX = rhs.mapSizeX;
		this->mapSizeY = rhs.mapSizeY;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Shared &c) {
	o << "Shared: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Shared::getValue() const	{	return (this->_val);	}
int		Shared::getLib() const	{	return (this->lib);	}
void	Shared::setCommand(eCommand command) {
	this->command = command;
}

void	Shared::setLib(eChoseLib lib) {
	this->lib = lib;
}

///////////////////////////////////////////////////////////////////////////////
