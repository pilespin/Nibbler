/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 17:48:46 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:08:28 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "IGraphic.hpp"
#include "Shared.hpp"
#include "Object.hpp"
#include "Ncurses.hpp"
#include <ncurses.h>

Ncurses::Ncurses() 						{	this->_val = 0;	}

Ncurses::~Ncurses()						{}

Ncurses::Ncurses(Ncurses const &src)	{	
	this->_val = src._val;
}

Ncurses	&Ncurses::operator=(Ncurses const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Ncurses &c) {
	o << "Ncurses: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Ncurses::getValue() const			{	return (this->_val);	}
void 	Ncurses::setShared(Shared *shared)	{	this->shared = shared;	}
///////////////////////////////////////////////////////////////////////////////

void	Ncurses::init() {
	initscr();
	noecho();
	raw();
}

void	Ncurses::quit() {
	endwin();
}

void	Ncurses::draw() {

	start_color();
	init_pair(BLOCK, COLOR_RED, COLOR_RED);
	init_pair(APPLE, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(8, COLOR_CYAN, COLOR_CYAN);
	init_pair(SNAKE, COLOR_GREEN, COLOR_GREEN);
	init_pair(IASNAKE, COLOR_BLUE, COLOR_BLUE);
	int i;
	int j = -1;
	while (++j < this->shared->mapSizeY)
	{
		i = -1;
		while (++i < this->shared->mapSizeX)
		{
			if (this->shared->map[j][i] == SNAKE)
			{
				attron(COLOR_PAIR(SNAKE));
				mvprintw(j*2, i*4, "    ");
				mvprintw(j*2 + 1, i*4, "    ");
				attroff(COLOR_PAIR(SNAKE));
			}
			else if (this->shared->map[j][i] == IASNAKE)
			{
				attron(COLOR_PAIR(IASNAKE));
				mvprintw(j*2, i*4, "    ");
				mvprintw(j*2 + 1, i*4, "    ");
				attroff(COLOR_PAIR(IASNAKE));
			}
			else if (this->shared->map[j][i] == BLOCK)
			{
				attron(COLOR_PAIR(BLOCK));
				mvprintw(j*2, i*4, "    ");
				mvprintw(j*2 + 1, i*4, "    ");
				attroff(COLOR_PAIR(BLOCK));
			}
			else if (this->shared->map[j][i] == APPLE)
			{
				attron(COLOR_PAIR(APPLE));
				mvprintw(j*2, i*4, "    ");
				mvprintw(j*2 + 1, i*4, "    ");
				attroff(COLOR_PAIR(APPLE));
			}
			else if (this->shared->map[j][i] == OFF)
			{
				attron(COLOR_PAIR(8));
				mvprintw(j*2, i*4, "    ");
				mvprintw(j*2 + 1, i*4, "    ");
				attroff(COLOR_PAIR(8));
			}
		}
	}
	mvprintw(j*2, i*4, "%s", "\n" );
	refresh();

}

int		Ncurses::getKey() {

	timeout(0.1);
	int ch;
	ch = (int)getch();
	
	if (ch == 27)
	{
		ch = (int)getch();
		if (ch == -1)
			shared->setCommand(eCommand::Escape);
	}
	else if (ch == 'D')
		shared->setCommand(eCommand::Left);
	else if (ch == 'C')
		shared->setCommand(eCommand::Right);
	else if (ch == 'A')
		shared->setCommand(eCommand::Up);
	else if (ch == 'B')
		shared->setCommand(eCommand::Down);
	else if (ch == '1')
		shared->setLib(eChoseLib::Lib1);
	else if (ch == '2')
		shared->setLib(eChoseLib::Lib2);
	else if (ch == '3')
		shared->setLib(eChoseLib::Lib3);
	return (ch - 48);
}


void	Ncurses::setWindowSize(int y, int x) {
	(void)x;
	(void)y;
}

void	Ncurses::setWindowName(std::string name) {
	(void)name;
}

extern "C"
{
	IGraphic *make_class()
	{
		return new Ncurses();
	}
}
