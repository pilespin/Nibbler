/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicLib.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:59:47 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/15 15:50:57 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>
#include "IGraphic.hpp"

class DynamicLib {

public:
	DynamicLib();
	~DynamicLib();
	DynamicLib(DynamicLib const &src);
	DynamicLib &operator=(DynamicLib const &rhs);

	int			getValue() const;
	IGraphic	*getClass() const;

	IGraphic	*createClass(std::string pathLib);
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
	int 		_val;
	void		*lib;
	IGraphic	*ptrClass;
};

std::ostream &operator<<(std::ostream &o, DynamicLib &c);
