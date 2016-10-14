/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 17:01:42 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Sdl.hpp"
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

Sdl::Sdl() {
	this->_val = 0;
	this->squareSize = 25;
	this->windowSizeX = 640;
	this->windowSizeY = 480;
	this->windowName = "Hello";
	this->shared = NULL;
	this->last_time = ft_utime();
}

Sdl::~Sdl()					{}

Sdl::Sdl(Sdl const &src)	{	*this = src;	}

Sdl	&Sdl::operator=(Sdl const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Sdl &c) {
	o << "Sdl: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int				Sdl::getValue() const			{	return (this->_val);		}
SDL_Window		*Sdl::getWindow() const			{	return (this->window);		}
SDL_Renderer	*Sdl::getRenderer() const		{	return (this->renderer);	}
void			Sdl::setShared(Shared *shared)	{	this->shared = shared;		}
void			Sdl::setWindowName(std::string name) {
	if (name.length() > 0)
		this->windowName = name;
	else
		throw Error("Error: Image not found");

}

SDL_Surface		*Sdl::getImage(std::string name) {	
	if (this->img[name])
		return (this->img[name]);
	else
	{
		std::cerr << "Image not found: " << name << std::endl;
		throw Error("Error: Image not found");
	}
}

void			Sdl::setWindowSize(int x, int y) {
	if (x > 0 && x < 16000 && y > 0 && y < 16000)
	{
		this->windowSizeX = x;
		this->windowSizeY = y;
	}
	else
		throw Error("Error: Window size is too small or too big");
}
///////////////////////////////////////////////////////////////////////////////

void	Sdl::init() {

	this->setWindowSize(this->shared->mapSizeX * this->squareSize, this->shared->mapSizeY * this->squareSize);
	this->setWindowName("Nibbler");
	this->createWindow();
	this->createRenderer();
    SDL_SetRenderDrawColor(this->getRenderer(), 175, 95, 255, 255); //BackGround
    this->loadImage("img/squareGreen.bmp", "squareGreen");

}

void	Sdl::quit() {

	SDL_DestroyWindow(this->getWindow());
	SDL_Quit();
}

void	Sdl::getKey() {

	SDL_Event   event;

	while (SDL_PollEvent(&event))
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE || 
			event.key.keysym.sym == SDLK_ESCAPE)
		{
			shared->setCommand(eCommand::Escape);
			std::cout << "GoodBye" << std::endl;
		}
            // if (event.type == SDL_MOUSEBUTTONDOWN){
        	//     quit = true;
        	// }
		else if (event.key.keysym.sym == SDLK_LEFT)
			shared->setCommand(eCommand::Left);
		else if (event.key.keysym.sym == SDLK_RIGHT)
			shared->setCommand(eCommand::Right);
		else if (event.key.keysym.sym == SDLK_UP)
			shared->setCommand(eCommand::Up);
		else if (event.key.keysym.sym == SDLK_DOWN)
			shared->setCommand(eCommand::Down);
	}
}

void	Sdl::draw() {

	int i;
	int j;

	SDL_RenderClear(this->getRenderer());

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

	SDL_RenderPresent(this->getRenderer());
}

void	Sdl::createWindow() {

	this->window = SDL_CreateWindow(this->windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowSizeX, 
		this->windowSizeY, 
		SDL_WINDOW_SHOWN);

	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating window");
	}
}

void	Sdl::createRenderer() {

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!this->renderer)
	{
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating renderer");
	}
}

SDL_Surface	*Sdl::loadImage(std::string path, std::string newname) {

	SDL_Surface     *bmp = SDL_LoadBMP(path.c_str());
	if (!bmp){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when creating window");
	}

	if (newname.length() > 0 && !this->img[newname])
		this->img[newname] = bmp;
	else
		throw Error("Error: An image with the same name already exist");

	return (bmp);
}

void	Sdl::DrawImageInRenderer(SDL_Surface *img, int x, int y) {

	SDL_Texture	*texture;
	SDL_Rect	dest;

	texture = SDL_CreateTextureFromSurface(this->renderer, img);
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(this->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

void	Sdl::empty() {

}

extern "C"
{
	IGraphic *make_class()
	{
		return new Sdl();
	}
}
