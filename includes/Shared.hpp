/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/15 20:31:05 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>

class Object;

class Shared {

public:
	Shared(int sizeX, int sizeY);
	~Shared();
	Shared(Shared const &src);
	Shared &operator=(Shared const &rhs);

	virtual int			getValue() const;
	virtual void		setCommand(eCommand command);

public: // private ////////////////////////////////////////////////////
	Shared();
	std::list<Object> snake;
	std::list<Object> obj;

	int 		_val;
	std::mutex 	mutex;
	int			**map;
	eCommand 	command;
	eCommand 	lastCommand;
	int 		mapSizeX;
	int 		mapSizeY;
};

std::ostream &operator<<(std::ostream &o, Shared &c);
