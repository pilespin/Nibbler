/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 19:58:53 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "DynamicLib.hpp"
#include "Shared.hpp"
#include "Core.hpp"
#include "Sdl.hpp"
#include "IGraphic.hpp"

int getWindowX(int ac, char **av)
{
    if (ac >= 2)
    {
        int nb = std::atoi(av[1]);
        return (nb);
    }
    return (20);
}

int getWindowY(int ac, char **av)
{
    if (ac >= 3)
    {
        int nb = std::atoi(av[2]);
        return (nb);
    }
    return (15);
}

int main(int ac, char **av)
{
    Core        *core;
    Shared      *shared;
    DynamicLib  *Lib_handler;
    
    try
    {
        Lib_handler = new DynamicLib();
        shared = new Shared(getWindowX(ac, av), getWindowY(ac, av));
        core = new Core(shared);

        core->setSpeed(0.25);
        Lib_handler->createClass("./libmysfml.so", shared);

        while (1)
        {
            if (shared->getLib() == NCURSES)
            {
                shared->setLib(eChoseLib::Nope);
                Lib_handler->createClass("./libmyncurses.so", shared);
            }
            if (shared->getLib() == SDL)
            {
                Lib_handler->createClass("./libmysdl.so", shared);
                shared->setLib(eChoseLib::Nope);
            }
            if (shared->getLib() == SFML)
            {
                Lib_handler->createClass("./libmysfml.so", shared);
                Lib_handler->createClass("./libmysfml.so", shared);
                shared->setLib(eChoseLib::Nope);
            }
            Lib_handler->getKey();
            core->start();
            Lib_handler->draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));   
        }
    }
    catch (std::exception &e)
    {
        if (shared)
        { 
            Lib_handler->createClass("libmyncurses.so", shared);
            Lib_handler->quit();
        }
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
