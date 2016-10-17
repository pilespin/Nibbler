/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/17 14:30:47 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "DynamicLib.hpp"
#include "Shared.hpp"
#include "Core.hpp"
#include "Sdl.hpp"
#include "IGraphic.hpp"

int main()
{
    Core        *core;
    Shared      *shared;
    IGraphic    *graf;
    int         key;

    try
    {
        shared = new Shared(15, 10);
        core = new Core(shared);

        DynamicLib  libsdl = DynamicLib();
        
        // graf = libsdl.createClass("./libmysdl.so");
        graf = libsdl.createClass("./libmyncurses.so");
        // graf = libsdl.createClass("./libmyallegro.so");

        graf->setShared(shared);
        graf->init();

        while (1)
        {
            key = graf->getKey();
            if (key == 1)
            {
                graf = libsdl.createClass("./libmysdl.so");
                graf->setShared(shared);
                graf->init();
            }
            if (key == 2)
            {
                graf = libsdl.createClass("./libmyncurses.so");
                graf->setShared(shared);
                graf->init();
            }
            core->start();
            graf->draw();
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));   
        }
    }
    catch (std::exception &e)
    {
        graf->quit();
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
