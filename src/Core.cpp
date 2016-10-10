/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/10 19:56:38 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Shared.hpp"
#include "Core.hpp"

Core::Core() 						{	this->_val = 0;	}

Core::Core(Shared	*shared) {
	this->shared = shared;
	this->shared->x = 500;
	this->shared->y = 50;
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

	while (1)
	{
		this->shared->mutex.lock();
		if (this->shared->command == eCommand::Up)
		{
			this->shared->y--;
			this->shared->command = eCommand::None;
		}
		else if (this->shared->command == eCommand::Down)
		{
			this->shared->command = eCommand::None;
			this->shared->y++;
		}
		else if (this->shared->command == eCommand::Left)
		{
			this->shared->command = eCommand::None;
			this->shared->x--;
		}
		else if (this->shared->command == eCommand::Right)
		{
			this->shared->command = eCommand::None;
			this->shared->x++;
		}
		else if (this->shared->command == eCommand::Escape)
		{
			exit(0);
		}
		this->shared->mutex.unlock();
		std::this_thread::sleep_for (std::chrono::milliseconds(10));
	}
}

void	Core::empty() {

}
