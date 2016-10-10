/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicLib.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:32:15 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/10 14:35:06 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DynamicLib.hpp"

DynamicLib::DynamicLib() 						{	this->_val = 0;	}

DynamicLib::~DynamicLib()						{}

DynamicLib::DynamicLib(DynamicLib const &src)	{	*this = src;	}

DynamicLib	&DynamicLib::operator=(DynamicLib const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, DynamicLib &c) {
	o << "DynamicLib: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		DynamicLib::getValue() const	{	return (this->_val);		}
void	*DynamicLib::getClass() const	{	return (this->ptrClass);	}
///////////////////////////////////////////////////////////////////////////////

void	*DynamicLib::createClass(std::string pathLib) {

	void    *func;

    this->lib = dlopen(pathLib.c_str(), RTLD_LAZY);
    if(!this->lib)
		throw Error("Error: an error occured when opening dynamic library");

    func = dlsym(this->lib, "make_class");
    if (!func)
		throw Error("Error: an error occured when loading function in library");

	typedef void *(*ptr)();

    ptr     pMaker = (ptr)func;
    this->ptrClass = pMaker();
    return (this->ptrClass);
}

void	DynamicLib::closeLib() {
    dlclose(this->lib);
}

void	DynamicLib::empty() {

}
