/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGraphic.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:56:45 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 17:40:58 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <project.hpp>
#include "Shared.hpp"

class IGraphic {
public:

	virtual void	init() = 0;
	virtual void	draw() = 0;
	virtual void	getKey() = 0;
	virtual void	setShared(Shared *shared) = 0;
	virtual 		~IGraphic( void ) {}

};
