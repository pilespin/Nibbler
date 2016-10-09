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
#include "Sdl.hpp"

int main()
{
    void    *lib;
    dynSdl  pMaker;
    
    lib = dlopen("./libmysdl.so", RTLD_LAZY);
    if(lib == NULL)
    {
        std::cerr << "dlopen : "<< dlerror() << std::endl; 
        exit(EXIT_FAILURE);
    }
    
    void *func = dlsym(lib, "make_sdl");
    if (func == NULL)
    {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    pMaker = (dynSdl)func;
    Sdl *sdl = pMaker();

    int test = sdl->getValue();
    std::cerr << "int: " << test << std::endl;
    
    sdl->start();

    dlclose(lib);

    return (0);
}
