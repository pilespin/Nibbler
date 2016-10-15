/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 19:32:01 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/15 19:54:20 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Object {

public:
	Object(int x, int y, int type);
	~Object();
	Object(Object const &src);
	Object &operator=(Object const &rhs);

	int			getValue() const;
	int			getType() const;
	int			getX() const;
	int			getY() const;
	void		empty();

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
	Object();
	int _val;
	int type;
	int x;
	int y;
};

std::ostream &operator<<(std::ostream &o, Object &c);
