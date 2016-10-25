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

IGraphic    *renewLib(IGraphic *lib, Shared *shared, bool init)
{
    IGraphic    *graf = NULL;

    if (!shared)
    {
        std::cerr << "Error: Shared memory is out" << std::endl;
        exit(0);
    }

    shared->lib = eChoseLib::Nope;
    graf = lib;
    graf->setShared(shared);
    if (init)
        graf->init();
    return (graf);
}

int main()
{
    Core        *core;
    Shared      *shared;
    IGraphic    *graf = NULL;
    IGraphic    *lib1 = NULL;
    IGraphic    *lib2 = NULL;
    IGraphic    *lib3 = NULL;
    DynamicLib  dLib = DynamicLib();

    try
    {
        shared = new Shared(20, 15);
        core = new Core(shared);

        lib1 = dLib.createClass("./libmysdl.so");
        lib2 = dLib.createClass("./libmyncurses.so");
        lib3 = dLib.createClass("./libmysfml.so");

        graf = renewLib(lib1, shared, true);

        while (1)
        {
            if (shared->getLib() == SDL)
                graf = renewLib(lib1, shared, false);
            else if (shared->getLib() == NCURSES)
                graf = renewLib(lib2, shared, true);
            else if (shared->getLib() == SFML)
                graf = renewLib(lib3, shared, true);

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
            graf = renewLib(lib2, shared, true);
            graf->quit();
        }
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
