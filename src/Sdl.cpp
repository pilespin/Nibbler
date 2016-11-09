/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 19:32:44 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "IGraphic.hpp"
#include "Shared.hpp"
#include "Object.hpp"
#include "Sdl.hpp"

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

///////////////////////////////   KEY   ///////////////////////////////////////
void 	Sdl::changeLibForLib1() 	{	this->shared->setLib(eChoseLib::Lib1);		}
void 	Sdl::changeLibForLib2() 	{	this->shared->setLib(eChoseLib::Lib2);		}
void 	Sdl::changeLibForLib3() 	{	this->shared->setLib(eChoseLib::Lib3);		}
void 	Sdl::moveToLeft() 			{	this->shared->setCommand(eCommand::Left);	}
void 	Sdl::moveToRight() 			{	this->shared->setCommand(eCommand::Right);	}
void 	Sdl::moveToUp() 			{	this->shared->setCommand(eCommand::Up);		}
void 	Sdl::moveToDown() 			{	this->shared->setCommand(eCommand::Down);	}
void 	Sdl::moveToEscape() 		{	this->shared->setCommand(eCommand::Escape);	}
///////////////////////////////   KEY   ///////////////////////////////////////

Sdl::Sdl() {
	this->_val = 0;
	this->squareSize = 28;
	this->windowSizeX = 640;
	this->windowSizeY = 480;
	this->windowName = "Hello";
	this->shared = NULL;
	this->last_time = ft_utime();
	this->window = NULL;
	this->renderer = NULL;
}

Sdl::~Sdl() {
	for (auto it = this->img.begin(); it != this->img.end(); it++) {
		if (it->second)
			SDL_FreeSurface(it->second);
	}
	this->quit();
}

Sdl::Sdl(Sdl const &src)	{		
	this->_val 			= src._val;
	this->shared 		= src.shared;
	this->windowName 	= src.windowName;
	this->squareSize 	= src.squareSize;
	this->windowSizeX 	= src.windowSizeX;
	this->windowSizeY 	= src.windowSizeY;
	this->last_time 	= src.last_time;
	this->window 		= src.window;
	this->renderer 		= src.renderer;
}

Sdl	&Sdl::operator=(Sdl const &rhs) {

	if (this != &rhs)
	{
		this->_val 			= rhs._val;
		this->shared 		= rhs.shared;
		this->windowName 	= rhs.windowName;
		this->squareSize 	= rhs.squareSize;
		this->windowSizeX 	= rhs.windowSizeX;
		this->windowSizeY 	= rhs.windowSizeY;
		this->last_time 	= rhs.last_time;
		this->window 		= rhs.window;
		this->renderer 		= rhs.renderer;
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
	{
		this->windowName.erase();
		this->windowName = name;
	}
	else
		throw Error("Error: Bad name");
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

	this->keymap[SDLK_1]				= &Sdl::changeLibForLib1;
	this->keymap[SDLK_2]				= &Sdl::changeLibForLib2;
	this->keymap[SDLK_3]				= &Sdl::changeLibForLib3;
	this->keymap[SDL_SCANCODE_LEFT]		= &Sdl::moveToLeft;
	this->keymap[SDL_SCANCODE_RIGHT]	= &Sdl::moveToRight;
	this->keymap[SDL_SCANCODE_UP]		= &Sdl::moveToUp;
	this->keymap[SDL_SCANCODE_DOWN]		= &Sdl::moveToDown;
	this->keymap[SDLK_ESCAPE]			= &Sdl::moveToEscape;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	this->setWindowSize(this->shared->mapSizeX * this->squareSize, this->shared->mapSizeY * this->squareSize);
	this->setWindowName("Nibbler SDL");
	this->createWindow();
	this->createRenderer();
    SDL_SetRenderDrawColor(this->getRenderer(), 175, 95, 255, 255); //BackGround
    
    this->loadImage("img/squareyellow.png", "squareyellow");
    this->loadImage("img/squareGreen.bmp", "squareGreen");
    this->loadImage("img/squareblue.png", "squareblue");
    this->loadImage("img/pnoyelle.png", "pnoyelle");
    this->loadImage("img/boobs.png", "boobs");
    this->loadImage("img/rock.png", "rock");

}

void	Sdl::quit() {
	SDL_DestroyRenderer(this->getRenderer());
	SDL_DestroyWindow(this->getWindow());
	SDL_Quit();
}

int 	Sdl::getKey(void) {

	SDL_Event   e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			shared->setCommand(eCommand::Escape);
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (keymap[e.key.keysym.sym])
				(this->*(keymap[e.key.keysym.sym]))();
		}
	}
	return (this->shared->command);
}

void	Sdl::draw() {

	SDL_RenderClear(this->getRenderer());

	for (auto it = this->shared->block.begin(); it != this->shared->block.end(); ++it) {
		if (it->getType() == BLOCK)
			this->DrawImageInRenderer(this->getImage("rock"), it->getX()*this->squareSize, it->getY()*this->squareSize);
	}
	
	for (auto it = this->shared->obj.begin(); it != this->shared->obj.end(); ++it) {
		if (it->getType() == APPLE)
			this->DrawImageInRenderer(this->getImage("boobs"), it->getX()*this->squareSize, it->getY()*this->squareSize);
	}

	for (auto it = this->shared->snake.begin(); it != this->shared->snake.end(); ++it) {
		if (it->getType() == SNAKE)
			this->DrawImageInRenderer(this->getImage("squareGreen"), it->getX()*this->squareSize, it->getY()*this->squareSize);
	}

	for (auto it = this->shared->IAsnake.begin(); it != this->shared->IAsnake.end(); ++it) {
		if (it->getType() == IASNAKE)
			this->DrawImageInRenderer(this->getImage("squareblue"), it->getX()*this->squareSize, it->getY()*this->squareSize);
	}

	// Head of snake
	this->DrawImageInRenderer(this->getImage("squareyellow"), this->shared->IAsnake.begin()->getX()*this->squareSize, this->shared->IAsnake.begin()->getY()*this->squareSize);
	this->DrawImageInRenderer(this->getImage("pnoyelle"), this->shared->snake.begin()->getX()*this->squareSize, this->shared->snake.begin()->getY()*this->squareSize);

	SDL_RenderPresent(this->getRenderer());
}

void	Sdl::createWindow() {

	this->window = SDL_CreateWindow(this->windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowSizeX, 
		this->windowSizeY, 
		SDL_WINDOW_SHOWN);

	if(!this->window)
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

	SDL_Surface     *bmp = IMG_Load(path.c_str());
	if (!bmp){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		throw Error("Error when atempt to load image: \"" + path + "\"");
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
	dest.w = this->squareSize;
	dest.h = this->squareSize;
	SDL_RenderCopy(this->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}

extern "C"
{
	IGraphic *make_class()
	{
		return new Sdl();
	}
	void        delete_class(IGraphic *graph)
	{
		delete graph;
	}
}
