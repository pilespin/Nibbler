/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 17:29:27 by pilespin         ###   ########.fr       */
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
    int         select_lib;

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
            graf->getKey();

            select_lib = shared->getLib();
            if (select_lib == 1)
            {
                shared->lib = eChoseLib::Nope;
                graf->quit();
                graf = libsdl.createClass("./libmysdl.so");
                graf->setShared(shared);
                graf->init();
            }
            if (select_lib == 2)
            {
                shared->lib = eChoseLib::Nope;
                graf->quit();
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
