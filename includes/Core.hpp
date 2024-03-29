/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/16 17:34:21 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Shared;
class Object;

class Core {

public:
	Core();
	Core(Shared	*shared);
	~Core();
	Core(Core const &src);
	Core &operator=(Core const &rhs);

	int			getValue() const;
	void		start();
	void 		setSpeed(double val);

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

	void 	moveToLeft();
	void 	moveToRight();
	void 	moveToUp();
	void 	moveToDown();

	void		setOnMap(int x, int y, int value);
	void		pushNewBlock(int y, int x);
	void		MoveSnake();
	void		MoveIASnake();
	void 		ignoreOpositeCommand();
	eCommand	getOpositeCommand(eCommand command);
	void		pushNewFood();
	int 		getRandomNumber(int max);
	void		pushNewBlockRandom(int max);
	void		pushNewSnake();
	void 		pushNewIASnake();

	bool 		IAcheckPosition(int y, int x);

	std::map<eCommand, void (Core::*)()>	keymap;

	int 	_val;
	bool	IAalive;
	int		IAheadX;
	int		IAheadY;
	int		headX;
	int		headY;
	Shared 	*shared;
	double	last_time;
	double 	secRefresh;

};

std::ostream &operator<<(std::ostream &o, Core &c);
