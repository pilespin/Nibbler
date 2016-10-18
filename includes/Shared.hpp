/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shared.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:44:03 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 19:27:55 by pilespin         ###   ########.fr       */
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
	virtual int			getOldLib() const;
	virtual void		setCommand(eCommand command);
	virtual void		setLib(eChoseLib lib);

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

public: // private ////////////////////////////////////////////////////
	Shared();
	std::list<Object> snake;
	std::list<Object> obj;
	std::list<Object> block;

	int 		_val;
	int			**map;
	eChoseLib 	lib;
	eChoseLib 	oldLib;
	eCommand 	command;
	eCommand 	lastCommand;
	int 		mapSizeX;
	int 		mapSizeY;
};

std::ostream &operator<<(std::ostream &o, Shared &c);
