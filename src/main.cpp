/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/09 19:19:42 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "DynamicLib.hpp"
#include "Sdl.hpp"

int main()
{
    DynamicLib libsdl = DynamicLib();

    Sdl *sdl = reinterpret_cast<Sdl*>(libsdl.createClass("./libmysdl.so"));

    int test = sdl->getValue();
    std::cerr << "int: " << test << std::endl;
    
    sdl->start();

    libsdl.closeLib();

    return (0);
}
