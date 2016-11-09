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
	this->_val 			= src._val;
	this->shared 		= src.shared;
	this->windowName 	= src.windowName;
	this->squareSize 	= src.squareSize;
	this->windowSizeX 	= src.windowSizeX;
	this->windowSizeY 	= src.windowSizeY;
	this->last_time 	= src.last_time;
}

Ncurses	&Ncurses::operator=(Ncurses const &rhs) {

	if (this != &rhs)
	{
		this->_val 			= rhs._val;
		this->shared 		= rhs.shared;
		this->windowName 	= rhs.windowName;
		this->squareSize 	= rhs.squareSize;
		this->windowSizeX 	= rhs.windowSizeX;
		this->windowSizeY 	= rhs.windowSizeY;
		this->last_time 	= rhs.last_time;
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
	this->keymap['1']	= &Ncurses::changeLibForLib1;
	this->keymap['2']	= &Ncurses::changeLibForLib2;
	this->keymap['3']	= &Ncurses::changeLibForLib3;
	this->keymap['D']	= &Ncurses::moveToLeft;
	this->keymap['C']	= &Ncurses::moveToRight;
	this->keymap['A']	= &Ncurses::moveToUp;
	this->keymap['B']	= &Ncurses::moveToDown;

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
	init_pair(OFF, COLOR_CYAN, COLOR_CYAN);
	init_pair(SNAKE, COLOR_GREEN, COLOR_GREEN);
	init_pair(IASNAKE, COLOR_BLUE, COLOR_BLUE);

	int i;
	int j = -1;
	while (++j < this->shared->mapSizeY)
	{
		i = -1;
		while (++i < this->shared->mapSizeX)
		{
			attron(COLOR_PAIR(this->shared->map[j][i]));
			mvprintw(j*2, i*4, "    ");
			mvprintw(j*2 + 1, i*4, "    ");
			attroff(COLOR_PAIR(this->shared->map[j][i]));
		}
	}
	mvprintw(j*2, i*4, "%s", "\n" );
	refresh();

}

///////////////////////////////   KEY   ///////////////////////////////////////
void 	Ncurses::changeLibForLib1() 	{	this->shared->setLib(eChoseLib::Lib1);		}
void 	Ncurses::changeLibForLib2() 	{	this->shared->setLib(eChoseLib::Lib2);		}
void 	Ncurses::changeLibForLib3() 	{	this->shared->setLib(eChoseLib::Lib3);		}
void 	Ncurses::moveToLeft() 			{	this->shared->setCommand(eCommand::Left);	}
void 	Ncurses::moveToRight() 			{	this->shared->setCommand(eCommand::Right);	}
void 	Ncurses::moveToUp() 			{	this->shared->setCommand(eCommand::Up);		}
void 	Ncurses::moveToDown() 			{	this->shared->setCommand(eCommand::Down);	}
void 	Ncurses::moveToEscape() 		{	this->shared->setCommand(eCommand::Escape);	}
///////////////////////////////   KEY   ///////////////////////////////////////

int		Ncurses::getKey() {

	timeout(0.1);
	int ch;
	ch = (int)getch();
	
	if (ch == 27)
	{
		ch = (int)getch();
		if (ch == -1)
		{
			this->quit();
			shared->setCommand(eCommand::Escape);
		}
	}
	else
	{			
		if (keymap[ch])
			(this->*(keymap[ch]))();
	}

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
	void        delete_class(IGraphic *graph)
	{
		delete graph;
	}
}
