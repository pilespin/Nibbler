/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGraphic.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:56:45 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:09:24 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Shared;

class IGraphic {
public:
	virtual void	init() = 0;
	virtual void	quit() = 0;
	virtual void	draw() = 0;
	virtual int		getKey() = 0;
	virtual void	setShared(Shared *shared) = 0;
	virtual void	setWindowSize(int y, int x) = 0;
	virtual void	setWindowName(std::string name) = 0;
	virtual 		~IGraphic( void ) {}
	
protected:
	Shared 			*shared;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	double			last_time;

};
