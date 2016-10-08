/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:53:16 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/08 21:18:32 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Sdl.hpp"

int main()
{
    Sdl sdl = Sdl();
    (void)sdl;

    sdl.createWindow();
    sdl.createRenderer();
    SDL_SetRenderDrawColor(sdl.getRenderer(), 175, 95, 255, 255); //BackGround

    bool        quit = false;
    SDL_Event   event;

    int x = 50;
    int y = 50;

    while(!quit)
    {
        SDL_WaitEvent(&event);

        if (event.window.event == SDL_WINDOWEVENT_CLOSE || 
            event.key.keysym.sym == SDLK_ESCAPE)
            quit = true;
        // if (event.type == SDL_MOUSEBUTTONDOWN){
        //     quit = true;
        // }
        if (event.key.keysym.sym == SDLK_LEFT)
            x--;
        if (event.key.keysym.sym == SDLK_RIGHT)
            x++;
        if (event.key.keysym.sym == SDLK_UP)
            y--;
        if (event.key.keysym.sym == SDLK_DOWN)
            y++;

        SDL_RenderClear(sdl.getRenderer());

        sdl.DrawImageInRenderer(sdl.loadImage("img/squareGreen.bmp"), x, y);
        // sdl.DrawImageInRenderer(sdl.loadImage("grey.jpg"), 250, 250);

        SDL_RenderPresent(sdl.getRenderer());

    }
    SDL_DestroyWindow(sdl.getWindow());
    SDL_Quit();
    return 0;
}
