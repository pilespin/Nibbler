/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/11 18:04:12 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Shared.hpp"
#include "Core.hpp"

Core::Core() 						{	this->_val = 0;	}

Core::Core(Shared	*shared) {
	this->shared = shared;
	this->headY = 5;
	this->headX = 5;
}

Core::~Core()						{}

Core::Core(Core const &src)	{	*this = src;	}

Core	&Core::operator=(Core const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Core &c) {
	o << "Core: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Core::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

void	Core::start() {

	this->setOnMap(this->headX, this->headY, SNAKE);
	while (1)
	{

		//////////////////////////////////debug//////
    	std::cout << "----------------------" << std::endl;
    	int j = -1;
    	while (++j < this->shared->mapSizeY)
    	{
    		int i = -1;
    		while (++i < this->shared->mapSizeX)
    			std::cout << this->shared->map[j][i] << " ";
    		std::cout << std::endl;
    	}
    	std::cout << "----------------------" << std::endl;
    	//////////////////////////////////debug//////
		this->shared->mutex.lock();
		if (this->shared->command == eCommand::Up)
		{
			this->setOnMap(this->headY, this->headX, OFF);
			this->headY--;
			this->setOnMap(this->headY, this->headX, SNAKE);
		}
		else if (this->shared->command == eCommand::Down)
		{
			this->setOnMap(this->headY, this->headX, OFF);
			this->headY++;
			this->setOnMap(this->headY, this->headX, SNAKE);
		}
		else if (this->shared->command == eCommand::Left)
		{
			this->setOnMap(this->headY, this->headX, OFF);
			this->headX--;
			this->setOnMap(this->headY, this->headX, SNAKE);
		}
		else if (this->shared->command == eCommand::Right)
		{
			this->setOnMap(this->headY, this->headX, OFF);
			this->headX++;
			this->setOnMap(this->headY, this->headX, SNAKE);
		}
		else if (this->shared->command == eCommand::Escape)
		{
			exit(0);
		}
		this->shared->mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void	Core::setOnMap(int x, int y, int value) {

	if (x >= 0 && x <= this->shared->mapSizeX && 
		y >= 0 && y <= this->shared->mapSizeY)
	{
		this->shared->map[x][y] = value;
	}
	else
		throw Error("Error: Value is out of map");
}

void	Core::empty() {

}
