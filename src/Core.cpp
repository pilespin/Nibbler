/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 16:44:19 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Shared.hpp"
#include "Core.hpp"

static double  ft_utime()
{
	int             sec;
	double          micro;
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}

Core::Core() 						{	this->_val = 0;	}

Core::Core(Shared	*shared) {
	this->shared = shared;
	this->headY = 5;
	this->headX = 5;
	this->setOnMap(this->headX, this->headY, SNAKE);
	this->last_time = ft_utime();
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
	double current = ft_utime();

	if (current > this->last_time + 1)
	{
		this->last_time = ft_utime();
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
	}

	this->shared->mutex.unlock();
}

void	Core::setOnMap(int y, int x, int value) {

	if (x >= 0 && x < this->shared->mapSizeX && 
		y >= 0 && y < this->shared->mapSizeY)
	{
		this->shared->map[y][x] = value;
	}
	else
		throw Error("Error: Value is out of map");
}

void	Core::empty() {

}
