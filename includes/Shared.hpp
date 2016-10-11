/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/11 16:18:05 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>

class Shared {

public:
	Shared(int sizeX, int sizeY);
	~Shared();
	Shared(Shared const &src);
	Shared &operator=(Shared const &rhs);

	virtual int			getValue() const;
	virtual void		setCommand(eCommand command);

	void		empty();

public:
	Shared();
	int 		_val;
	std::mutex 	mutex; 
	int			**map;
	eCommand 	command;
	int 		mapSizeX;
	int 		mapSizeY;
};

std::ostream &operator<<(std::ostream &o, Shared &c);
