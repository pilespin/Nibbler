/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/10 19:52:14 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "DynamicLib.hpp"
#include "Shared.hpp"
#include "Core.hpp"
#include "Sdl.hpp"

Shared      *shared;
Core        *core;

void foo()
{
    core->start();
}

int main()
{
    shared = new Shared();
    core = new Core(shared);

    (void)core;
    (void)shared;

    DynamicLib  libsdl = DynamicLib();

    Sdl *sdl = reinterpret_cast<Sdl*>(libsdl.createClass("./libmysdl.so"));

    sdl->setShared(shared);
    std::thread first(foo);
    sdl->start();
    
    first.join();

    return (0);
}
