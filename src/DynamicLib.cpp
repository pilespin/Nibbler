/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicLib.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:32:15 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 18:11:01 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "IGraphic.hpp"
#include "DynamicLib.hpp"

DynamicLib::DynamicLib()
{	
	this->lib = NULL;
	this->constr = NULL;	
	this->destr = NULL;	
	this->graph = NULL;	
}

DynamicLib::~DynamicLib()
{
	this->closeLib();
}

DynamicLib::DynamicLib(DynamicLib const &src)
{	
	this->lib = src.lib;
	this->constr = src.constr;
	this->destr = src.destr;
	this->graph = src.graph;
}

DynamicLib	&DynamicLib::operator=(DynamicLib const &rhs) {

	if (this != &rhs)
	{
		this->lib = rhs.lib;
		this->constr = rhs.constr;
		this->destr = rhs.destr;
		this->graph = rhs.graph;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, DynamicLib &c) {
	(void)c;
	o << "DynamicLib " << std::endl;
	return (o);
}
void	DynamicLib::draw()
{
	if (this->graph == NULL)
		throw Error("Dynamic Library not loaded.");
	this->graph->draw();
}

int		DynamicLib::getKey()
{
	if (this->graph == NULL)
		throw Error("Dynamic Library not loaded.");
	return (this->graph->getKey());
}

void  DynamicLib::createClass(std::string pathLib, Shared *shared) {

	void		*constr_pre;
	void		*destr_pre;

	if (this->lib != NULL)
		this->closeLib();
	this->lib = dlopen(pathLib.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if(this->lib == NULL)
	{
		// std::cout<< dlerror()<<std::endl;
		throw Error("Error: an error occured when opening dynamic library");
	}

	constr_pre = (dlsym(this->lib, "make_class"));
	if (constr_pre == NULL)
	{
		throw Error("Error: an error occured when loading function constructeur in library");
	}
	destr_pre = (dlsym(this->lib, "delete_class"));
	if (destr_pre == NULL)
		throw Error("Error: an error occured when loading function destructeur in library");
	

	this->constr = (IGraphic 	*(*)(void))(constr_pre);
	this->destr = (void(*)(IGraphic *))(destr_pre);

	this->graph = (this->constr)();
	this->graph->setShared(shared);
	this->graph->init();
}

void	DynamicLib::closeLib() {

	if (this->lib == NULL)
		throw Error("error in closing library");
	this->graph->quit();
	(this->destr)(this->graph);
	if (dlclose(this->lib) != 0)
		throw Error("error in closing library");
	this->lib = NULL;
	this->constr = NULL;	
	this->destr = NULL;	
	this->graph = NULL;
}
