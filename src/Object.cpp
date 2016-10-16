/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 19:31:52 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/16 15:11:58 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Object.hpp"

Object::Object() 						{	this->_val = 0;	}
Object::Object(int y, int x, int type) {

	this->_val 	= 0;	
	this->type 	= type;	
	this->x 	= x;	
	this->y 	= y;	
}

Object::~Object()						{}

Object::Object(Object const &src)	{
	this->_val 	= src._val;
	this->type 	= src.type;
	this->x 	= src.x;
	this->y 	= src.y;
}

Object	&Object::operator=(Object const &rhs) {

	if (this != &rhs)
	{
		this->_val 	= rhs._val;
		this->type 	= rhs.type;
		this->x 	= rhs.x;
		this->y 	= rhs.y;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Object &c) {
	o << "Object: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Object::getValue() const	{	return (this->_val);	}
int		Object::getX() const		{	return (this->x);	}
int		Object::getY() const		{	return (this->y);	}
int		Object::getType() const		{	return (this->type);	}
///////////////////////////////////////////////////////////////////////////////
void	Object::empty() {

}
