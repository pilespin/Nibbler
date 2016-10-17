/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/17 14:31:59 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Shared;

class Sdl : public IGraphic {

public:
	Sdl();
	~Sdl();
	Sdl(Sdl const &src);
	Sdl &operator=(Sdl const &rhs);

	int		getValue() const;

	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);
	void	setShared(Shared *shared);

	void	init();
	int 	getKey();
	void	quit();
	void	draw();

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
	SDL_Window		*getWindow() const;
	SDL_Renderer 	*getRenderer() const;
	SDL_Surface		*getImage(std::string name);
	SDL_Surface		*loadImage(std::string path, std::string newname);

	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			createWindow();
	void			createRenderer();
	void			empty();

	std::map< std::string, SDL_Surface * > 	img;
	
	int 			_val;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
