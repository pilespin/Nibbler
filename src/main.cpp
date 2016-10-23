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
#include <SFML/Graphics.hpp>

IGraphic    *renewLib(DynamicLib dLib, Shared *shared, std::string path)
{
    IGraphic    *graf = NULL;

    if (!shared)
    {
        std::cerr << "Error: Shared memory is out" << std::endl;
        exit(0);
    }

    shared->lib = eChoseLib::Nope;
    // graf->quit();
    dLib.closeLib();
    graf = dLib.createClass(path.c_str());
    graf->setShared(shared);
    graf->init();
    return (graf);
}

int main()
{
    Core        *core;
    Shared      *shared;
    IGraphic    *graf = NULL;
    DynamicLib  dLib = DynamicLib();


////////////////////////////////WORKING /////////////
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
////////////////////////////////WORKING /////////////



    try
    {
        shared = new Shared(15, 10);
        core = new Core(shared);

        // graf = renewLib(dLib, shared, "./libmysdl.so");
        // graf = renewLib(dLib, shared, "./libmyncurses.so");
        graf = renewLib(dLib, shared, "./libmysfml.so");

        while (1)
        {
            if (shared->getLib() == SDL)
            {
                if (graf)
                    delete graf;
                // graf->quit();
                graf = renewLib(dLib, shared, "./libmysdl.so");
            }
            else if (shared->getLib() == NCURSES)
            {
                if (graf)
                    delete graf;
                // graf->quit();
                graf = renewLib(dLib, shared, "./libmyncurses.so");
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
            if (graf)
                delete graf;
            graf = renewLib(dLib, shared, "./libmyncurses.so");
            graf->quit();
        }
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
