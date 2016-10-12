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
Shared      *shared;
bool         g_exit = false;

void ThreadAlgo()
{
    try
    {
        core->start();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        g_exit = true;   
    }
}

void ThreadSdl()
{
    try
    {
        DynamicLib  libsdl = DynamicLib();
        
        Sdl *sdl = reinterpret_cast<Sdl*>(libsdl.createClass("./libmysdl.so"));

        sdl->setShared(shared);
        sdl->start();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        g_exit = true;   
    }
}

int main()
{
    try
    {
        shared = new Shared(20, 10);
        core = new Core(shared);

        std::thread Talgo(ThreadAlgo);
        std::thread TSdl(ThreadSdl);
        
        while (1)
        {
            if (g_exit)
                exit(0);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
