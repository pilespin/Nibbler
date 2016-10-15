/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Allegro.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 17:01:42 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Allegro.hpp"
#include "Shared.hpp"

static double  ft_utime()
{
	int             sec;
	double          micro;
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}

Allegro::Allegro() {
	this->_val = 0;
	this->squareSize = 25;
	this->windowSizeX = 640;
	this->windowSizeY = 480;
	this->windowName = "Hello";
	this->shared = NULL;
	this->last_time = ft_utime();
}

Allegro::~Allegro()					{}

Allegro::Allegro(Allegro const &src)	{	*this = src;	}

Allegro	&Allegro::operator=(Allegro const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Allegro &c) {
	o << "Allegro: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int				Allegro::getValue() const			{	return (this->_val);		}
Allegro_Window		*Allegro::getWindow() const			{	return (this->window);		}
Allegro_Renderer	*Allegro::getRenderer() const		{	return (this->renderer);	}
void			Allegro::setShared(Shared *shared)	{	this->shared = shared;		}
void			Allegro::setWindowName(std::string name) {
	if (name.length() > 0)
		this->windowName = name;
	else
		throw Error("Error: Image not found");

}

Allegro_Surface		*Allegro::getImage(std::string name) {	
	if (this->img[name])
		return (this->img[name]);
	else
	{
		std::cerr << "Image not found: " << name << std::endl;
		throw Error("Error: Image not found");
	}
}

void			Allegro::setWindowSize(int x, int y) {
	if (x > 0 && x < 16000 && y > 0 && y < 16000)
	{
		this->windowSizeX = x;
		this->windowSizeY = y;
	}
	else
		throw Error("Error: Window size is too small or too big");
}
///////////////////////////////////////////////////////////////////////////////

void	Allegro::init() {

	this->setWindowSize(this->shared->mapSizeX * this->squareSize, this->shared->mapSizeY * this->squareSize);
	this->setWindowName("Nibbler");
	this->createWindow();
	this->createRenderer();
    Allegro_SetRenderDrawColor(this->getRenderer(), 175, 95, 255, 255); //BackGround
    this->loadImage("img/squareGreen.bmp", "squareGreen");

}

void	Allegro::quit() {

	Allegro_DestroyWindow(this->getWindow());
	Allegro_Quit();
}

void	Allegro::getKey() {

	Allegro_Event   event;

	while (Allegro_PollEvent(&event))
	{
		if (event.window.event == Allegro_WINDOWEVENT_CLOSE || 
			event.key.keysym.sym == AllegroK_ESCAPE)
		{
			shared->setCommand(eCommand::Escape);
			std::cout << "GoodBye" << std::endl;
		}
            // if (event.type == Allegro_MOUSEBUTTONDOWN){
        	//     quit = true;
        	// }
		else if (event.key.keysym.sym == AllegroK_LEFT)
			shared->setCommand(eCommand::Left);
		else if (event.key.keysym.sym == AllegroK_RIGHT)
			shared->setCommand(eCommand::Right);
		else if (event.key.keysym.sym == AllegroK_UP)
			shared->setCommand(eCommand::Up);
		else if (event.key.keysym.sym == AllegroK_DOWN)
			shared->setCommand(eCommand::Down);
	}
}

void	Allegro::draw() {

	int i;
	int j;

	Allegro_RenderClear(this->getRenderer());

	j = -1;
	while (++j < this->shared->mapSizeY)
	{
		i = -1;
		while (++i < this->shared->mapSizeX)
		{
			if (this->shared->map[j][i] == 1)
				this->DrawImageInRenderer(this->getImage("squareGreen"), i*this->squareSize, j*this->squareSize);
		}
	}

	Allegro_RenderPresent(this->getRenderer());
}

void	Allegro::createWindow() {

	this->window = Allegro_CreateWindow(this->windowName.c_str(),
		Allegro_WINDOWPOS_CENTERED,
		Allegro_WINDOWPOS_CENTERED,
		this->windowSizeX, 
		this->windowSizeY, 
		Allegro_WINDOW_SHOWN);

	if(!window)
	{
		std::cout << Allegro_GetError() << std::endl;
		Allegro_Quit();
		throw Error("Error when creating window");
	}
}

void	Allegro::createRenderer() {

	this->renderer = Allegro_CreateRenderer(this->window, -1, Allegro_RENDERER_ACCELERATED | Allegro_RENDERER_PRESENTVSYNC);
	if (!this->renderer)
	{
		Allegro_DestroyWindow(this->window);
		std::cout << Allegro_GetError() << std::endl;
		Allegro_Quit();
		throw Error("Error when creating renderer");
	}
}

Allegro_Surface	*Allegro::loadImage(std::string path, std::string newname) {

	Allegro_Surface     *bmp = Allegro_LoadBMP(path.c_str());
	if (!bmp){
		Allegro_DestroyRenderer(this->renderer);
		Allegro_DestroyWindow(this->window);
		std::cout << Allegro_GetError() << std::endl;
		Allegro_Quit();
		throw Error("Error when creating window");
	}

	if (newname.length() > 0 && !this->img[newname])
		this->img[newname] = bmp;
	else
		throw Error("Error: An image with the same name already exist");

	return (bmp);
}

void	Allegro::DrawImageInRenderer(Allegro_Surface *img, int x, int y) {

	Allegro_Texture	*texture;
	Allegro_Rect	dest;

	texture = Allegro_CreateTextureFromSurface(this->renderer, img);
	dest.x = x;
	dest.y = y;
	Allegro_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	Allegro_RenderCopy(this->renderer, texture, NULL, &dest);
	Allegro_DestroyTexture(texture);
}

void	Allegro::empty() {

}

extern "C"
{
	IGraphic *make_class()
	{
		return new Allegro();
	}
}
