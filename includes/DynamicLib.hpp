/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicLib.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:59:47 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/16 15:06:04 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IGraphic.hpp"

class DynamicLib {

public:
	DynamicLib();
	~DynamicLib();
	DynamicLib(DynamicLib const &src);
	DynamicLib &operator=(DynamicLib const &rhs);


	void		draw();
	void		quit();
	int			getKey();
	void		delete_current();
	void 		createClass(std::string pathLib, Shared *shared);
	void		closeLib();

	class Error : public std::exception {
	public:
		Error(std::string str) { 
			this->line += str; 
		}
		virtual const char *what() const throw() {
			return (this->line.c_str());
		}
	private:
		std::string line;
	};

private:
	void		*lib;
	IGraphic	*graph;
	IGraphic 	*(*constr)(void);
	void 		(*destr)(IGraphic *);
};

std::ostream &operator<<(std::ostream &o, DynamicLib &c);
