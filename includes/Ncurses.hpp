/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 17:48:46 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:17:43 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Shared;

class Ncurses : public IGraphic {

public:
	Ncurses();
	~Ncurses();
	Ncurses(Ncurses const &src);
	Ncurses &operator=(Ncurses const &rhs);

	int		getValue() const;

	void	init();
	void	quit();
	void	draw();
	int		getKey();
	void	setShared(Shared *shared);
	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);

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
	int _val;
};

std::ostream &operator<<(std::ostream &o, Ncurses &c);
