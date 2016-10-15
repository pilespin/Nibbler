/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/15 20:56:07 by pilespin         ###   ########.fr       */
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
    try
    {
        Core        *core;
        Shared      *shared;
        IGraphic    *graf;

        shared = new Shared(20, 20);
        core = new Core(shared);

        DynamicLib  libsdl = DynamicLib();
        
        graf = libsdl.createClass("./libmysdl.so");

        graf->setShared(shared);
        graf->init();

        while (1)
        {
            graf->getKey();
            core->start();
            graf->draw();
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));   
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
