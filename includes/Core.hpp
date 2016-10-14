/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 16:32:10 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shared.hpp"
#include <iostream>

class Core {

public:
	Core();
	Core(Shared	*shared);
	~Core();
	Core(Core const &src);
	Core &operator=(Core const &rhs);

	int			getValue() const;
	void		empty();
	void		start();
	void		setOnMap(int x, int y, int value);

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
	int 	_val;
	int		headX;
	int		headY;
	Shared 	*shared;
	double	last_time;

};

std::ostream &operator<<(std::ostream &o, Core &c);
