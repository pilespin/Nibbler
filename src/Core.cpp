/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 18:52:38 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Object.hpp"
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
	std::srand(time(NULL));
	this->shared = shared;
	this->shared->command = eCommand::Right;
	this->shared->lastCommand = eCommand::Right;
	this->IAheadY = this->shared->mapSizeY - 1;
	this->IAheadX = 6;
	this->headY = 0;
	this->headX = 6;
	this->IAalive = true;
	this->pushNewSnake();
	this->pushNewIASnake();
	this->pushNewBlockRandom(this->shared->mapSizeX / 5);
	this->pushNewFood();
	this->last_time = ft_utime();
	this->secRefresh = 0.3;
}

Core::~Core() {
}

Core::Core(Core const &src)	{	
	*this = src;	
}

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

void Core::pushNewBlockRandom(int max) {

	int i = -1;
	while (++i < max)
		this->pushNewBlock(getRandomNumber(this->shared->mapSizeY - 2) + 1, getRandomNumber(this->shared->mapSizeX - 2 ) + 1);

}

void Core::pushNewIASnake() {

	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX -4, IASNAKE));
	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX -3, IASNAKE));
	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX -2, IASNAKE));
	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX -1, IASNAKE));
	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX, IASNAKE));

	for (auto it = this->shared->IAsnake.begin(); it != this->shared->IAsnake.end(); ++it) {
		this->setOnMap(it->getY(), it->getX(), IASNAKE);
	}
}

void Core::pushNewSnake() {

	this->shared->snake.push_front(Object(this->headY, this->headX -4, SNAKE));
	this->shared->snake.push_front(Object(this->headY, this->headX -3, SNAKE));
	this->shared->snake.push_front(Object(this->headY, this->headX -2, SNAKE));
	this->shared->snake.push_front(Object(this->headY, this->headX -1, SNAKE));
	this->shared->snake.push_front(Object(this->headY, this->headX, SNAKE));

	for (auto it = this->shared->snake.begin(); it != this->shared->snake.end(); ++it) {
		this->setOnMap(it->getY(), it->getX(), SNAKE);
	}
}

void Core::pushNewBlock(int y, int x) {

	this->shared->block.push_front(Object(y, x, BLOCK));
	this->setOnMap(y, x, BLOCK);
}

eCommand	Core::getOpositeCommand(eCommand command) {

	if (command == eCommand::Up)
		return (eCommand::Down);
	else if (command == eCommand::Down)
		return (eCommand::Up);
	else if (command == eCommand::Left)
		return (eCommand::Right);
	else if (command == eCommand::Right)
		return (eCommand::Left);
	else
		return (eCommand::None);

}

void Core::ignoreOpositeCommand() {

	if (this->shared->lastCommand == this->getOpositeCommand(this->shared->command))
		this->shared->command = this->shared->lastCommand;

}

bool Core::IAcheckPosition(int y, int x)
{
	if (x >= 0 && x <= this->shared->mapSizeX - 1 && 
		y >= 0 && y <= this->shared->mapSizeY - 1)
	{
		if (this->shared->map[y][x] == OFF)
			return (true);
		if (this->shared->map[y][x] == APPLE)
			return (true);
	}
	return (false);
}

void Core::MoveIASnake() {

	if (!this->IAalive)
		return;
	
	this->setOnMap(this->shared->IAsnake.back().getY(), this->shared->IAsnake.back().getX(), OFF);
	this->shared->IAsnake.pop_back();

	bool right 	= IAcheckPosition(this->IAheadY, this->IAheadX + 1);
	bool left 	= IAcheckPosition(this->IAheadY, this->IAheadX - 1);
	bool up 	= IAcheckPosition(this->IAheadY - 1, this->IAheadX);
	bool down 	= IAcheckPosition(this->IAheadY + 1, this->IAheadX);


	if (up && this->shared->obj.begin()->getY() < this->IAheadY)
		this->IAheadY--;
	else if (down && this->shared->obj.begin()->getY() > this->IAheadY)
		this->IAheadY++;
	else if (left && this->shared->obj.begin()->getX() < this->IAheadX)
		this->IAheadX--;
	else if (right && this->shared->obj.begin()->getX() > this->IAheadX)
		this->IAheadX++;
	else
	{
		if (right)
			this->IAheadX++;
		else if (left)
			this->IAheadX--;
		else if (up)
			this->IAheadY--;
		else if (down)
			this->IAheadY++;
		else
			this->IAalive = false;
	}

	this->setOnMap(this->IAheadY, this->IAheadX, IASNAKE);
	this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX, IASNAKE));

}

void Core::MoveSnake() {
	
	this->setOnMap(this->shared->snake.back().getY(), this->shared->snake.back().getX(), OFF);
	this->shared->snake.pop_back();

	if (this->shared->command == eCommand::Up)
		this->headY--;
	else if (this->shared->command == eCommand::Down)
		this->headY++;
	else if (this->shared->command == eCommand::Left)
		this->headX--;
	else if (this->shared->command == eCommand::Right)
		this->headX++;

	this->setOnMap(this->headY, this->headX, SNAKE);
	this->shared->snake.push_front(Object(this->headY, this->headX, SNAKE));

}

int Core::getRandomNumber(int max) {
	if (max <= 0)
		return (0);
	int x = std::rand() % max;
	return (x);
}

void Core::pushNewFood() {

	int x = getRandomNumber(this->shared->mapSizeX);
	int y = getRandomNumber(this->shared->mapSizeY);

	while (this->shared->map[y][x] != OFF)
	{
		x = getRandomNumber(this->shared->mapSizeX);
		y = getRandomNumber(this->shared->mapSizeY);
	}

	this->shared->obj.push_front(Object(y, x, APPLE));
	this->shared->map[y][x] = APPLE;
}


void	Core::start() {

	double current = ft_utime();

	if (current > this->last_time + this->secRefresh || 
		(this->shared->command != this->shared->lastCommand && 
			this->shared->lastCommand != this->getOpositeCommand(this->shared->command)))
	{
		////////////////////////////////debug//////
			// std::cout << "----------------------" << std::endl;
			// int j = -1;
			// while (++j < this->shared->mapSizeY)
			// {
			// 	int i = -1;
			// 	while (++i < this->shared->mapSizeX)
			// 		std::cout << this->shared->map[j][i] << " ";
			// 	std::cout << std::endl;
			// }
			// std::cout << "----------------------" << std::endl;
    	////////////////////////////////debug//////

		this->last_time = ft_utime();

		this->ignoreOpositeCommand();
		this->MoveSnake();	
		this->MoveIASnake();

		if (this->shared->command == eCommand::Escape)
		{
			throw Error("GoodBye");
		}

		this->shared->lastCommand = this->shared->command;

	}
}

void	Core::setOnMap(int y, int x, int value) {

	if (x >= 0 && x < this->shared->mapSizeX && 
		y >= 0 && y < this->shared->mapSizeY)
	{
		if (this->shared->map[y][x] == SNAKE && value == SNAKE)
			throw Error("You are not eatable");
		if (this->shared->map[this->headY][this->headX] == APPLE)
		{
			this->shared->snake.push_front(Object(this->headY, this->headX, SNAKE));
			this->shared->obj.pop_back();
			this->pushNewFood();
		}
		if (this->shared->map[this->IAheadY][this->IAheadX] == APPLE)
		{
			this->shared->IAsnake.push_front(Object(this->IAheadY, this->IAheadX, IASNAKE));
			this->shared->obj.pop_back();
			this->pushNewFood();
		}
		if (this->shared->map[this->headY][this->headX] == BLOCK ||
			this->shared->map[this->headY][this->headX] == IASNAKE)
			throw Error("Error: You are dead");

		this->shared->map[y][x] = value;
	}
	else
		throw Error("Error: You are so far");
}
