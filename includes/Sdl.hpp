/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/08 21:16:51 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>

class Sdl {

public:
	Sdl();
	~Sdl();
	Sdl(Sdl const &src);
	Sdl &operator=(Sdl const &rhs);

	int				getValue() const;
	SDL_Window		*getWindow() const;
	SDL_Renderer 	*getRenderer() const;
	SDL_Surface		*getImage(std::string name);

	void			setWindowSize(int x, int y);
	void			setWindowName(std::string name);

	void			createWindow();
	void			createRenderer();
	SDL_Surface		*loadImage(std::string path, std::string newname);
	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			empty();

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
	std::map< std::string, SDL_Surface * > 	img;

	int 			_val;
	std::string		windowName;
	int 			windowSizeX;
	int 			windowSizeY;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
