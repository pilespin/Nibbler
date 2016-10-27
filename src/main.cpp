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

IGraphic    *renewLib(Shared *shared, eChoseLib which)
{
    DynamicLib  dLib = DynamicLib();
    IGraphic    *lib = NULL;

    if (!shared)
    {
        std::cerr << "Error: Shared memory is out" << std::endl;
        exit(0);
    }
    if (which == eChoseLib::Lib1)
        lib = dLib.createClass("./libmysdl.so");
    if (which == eChoseLib::Lib2)
        lib = dLib.createClass("./libmyncurses.so");
    if (which == eChoseLib::Lib3)
    {
        std::cout<<"make"<<std::endl;
        lib = dLib.createClass("./libmysfml.so");
    }
    shared->lib = eChoseLib::Nope;
    
    std::cout<<"lib"<<std::endl;
        
    if (lib == NULL)
    {
        std::cout<<"libNULL"<<std::endl;
        exit(0);
    }
    lib->setShared(shared);
    lib->init();
    return (lib);
}

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
    IGraphic    *graf = NULL;

    try
    {

        shared = new Shared(getWindowX(ac, av), getWindowY(ac, av));
        core = new Core(shared);

        core->setSpeed(0.25);

        graf = renewLib(shared, eChoseLib::Lib3);

        while (1)
        {
            if (shared->getLib() == SDL)
            {
                 graf->quit();
                delete graf;
                graf = renewLib(shared, eChoseLib::Lib1);
            }
            else if (shared->getLib() == NCURSES)
            {
                 graf->quit();
                delete graf;
                graf = renewLib(shared, eChoseLib::Lib2);
            }
            else if (shared->getLib() == SFML)
            {
                graf->quit();
                delete graf;

                graf = renewLib(shared, eChoseLib::Lib3);
            }

            graf->getKey();
            core->start();
            graf->draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));   
        }
    }
    catch (std::exception &e)
    {
        if (shared)
        {
            graf->quit();
        }
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
