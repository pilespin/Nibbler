/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 16:58:24 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Object;

class Shared {

public:
	Shared(int sizeX, int sizeY);
	~Shared();
	Shared(Shared const &src);
	Shared &operator=(Shared const &rhs);

	virtual int			getValue() const;
	virtual int			getLib() const;
	virtual void		setCommand(eCommand command);
	virtual void		setLib(eChoseLib lib);

public: // private ////////////////////////////////////////////////////
	Shared();
	std::list<Object> snake;
	std::list<Object> obj;
	std::list<Object> block;

	int 		_val;
	int			**map;
	eChoseLib 	lib;
	eCommand 	command;
	eCommand 	lastCommand;
	int 		mapSizeX;
	int 		mapSizeY;
};

std::ostream &operator<<(std::ostream &o, Shared &c);
