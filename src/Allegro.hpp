/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Allegro.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 16:27:36 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shared.hpp"
#include "IGraphic.hpp"
#include <project.hpp>

class Allegro : public IGraphic{

public:
	Allegro();
	~Allegro();
	Allegro(Allegro const &src);
	Allegro &operator=(Allegro const &rhs);

	virtual int				getValue() const;
	virtual Allegro_Window		*getWindow() const;
	virtual Allegro_Renderer 	*getRenderer() const;
	virtual Allegro_Surface		*getImage(std::string name);

	virtual void			setWindowSize(int y, int x);
	virtual void			setWindowName(std::string name);
	virtual void			setShared(Shared *shared);

	virtual void			createWindow();
	virtual void			createRenderer();
	virtual Allegro_Surface		*loadImage(std::string path, std::string newname);
	virtual void			DrawImageInRenderer(Allegro_Surface *img, int x, int y);
	virtual void			init();
	virtual void			getKey();
	virtual void			quit();
	virtual void			draw();
	virtual void			empty();

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
	std::map< std::string, Allegro_Surface * > 	img;

	Shared 			*shared;
	int 			_val;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	Allegro_Window 		*window;
	Allegro_Renderer	*renderer;
	double			last_time;
};

std::ostream &operator<<(std::ostream &o, Allegro &c);
