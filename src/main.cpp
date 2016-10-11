/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/11 17:56:31 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "DynamicLib.hpp"
#include "Shared.hpp"
#include "Core.hpp"
#include "Sdl.hpp"

Core        *core;

void foo()
{
    core->start();
}

int main()
{
    Shared      *shared;

    shared = new Shared(20, 10);
    core = new Core(shared);

    DynamicLib  libsdl = DynamicLib();
    
    Sdl *sdl = reinterpret_cast<Sdl*>(libsdl.createClass("./libmysdl.so"));

    // shared->mapSizeX = 10;
    // shared->mapSizeY = 10;

    sdl->setShared(shared);
    std::thread first(foo);
    sdl->start();
    
    first.join();

    return (0);
}
