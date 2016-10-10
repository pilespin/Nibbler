/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/10 19:19:20 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>

class Shared {

public:
	Shared();
	~Shared();
	Shared(Shared const &src);
	Shared &operator=(Shared const &rhs);

	virtual int			getValue() const;
	virtual int 		getX() const;
	virtual int 		getY() const;
	virtual void		setCommand(eCommand command);
	virtual void 		setX(int x);
	virtual void 		setY(int y);

	void		empty();

public:
	eCommand 	command;
	std::mutex 	mutex; 
	int 		_val;
	int 		x;
	int 		y;
};

std::ostream &operator<<(std::ostream &o, Shared &c);
