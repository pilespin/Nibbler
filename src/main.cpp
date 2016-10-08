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


    // // std::string     imagePath = getResourcePath("Lesson1") + "hello.bmp";
    // SDL_Surface     *bmp = SDL_LoadBMP("hello.bmp");
    // if (!bmp){
    //     SDL_DestroyRenderer(ren);
    //     SDL_DestroyWindow(win);
    //     std::cout << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_Texture     *tex = SDL_CreateTextureFromSurface(ren, bmp);
    // SDL_FreeSurface(bmp);
    // if (!tex){
    //     SDL_DestroyRenderer(ren);
    //     SDL_DestroyWindow(win);
    //     std::cout << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }


    bool        end = false;
    SDL_Event   event;

    SDL_SetRenderDrawColor(sdl.getRenderer(), 175, 95, 255, 255);
    while(!end)
    {
        SDL_WaitEvent(&event);

        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            end = true;

        SDL_RenderClear(sdl.getRenderer());
        // SDL_RenderCopy(sdl.getRenderer(), tex, NULL, NULL);

        // SDL_Texture *texture;
        // SDL_Rect    dest;

        // SDL_Surface     *bmp2 = SDL_LoadBMP("de.png");

        // texture = SDL_CreateTextureFromSurface(ren, bmp2);
        // dest.x = 50;
        // dest.y = 50;
        // SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        // SDL_RenderCopy(ren, texture, NULL, &dest);
        // SDL_DestroyTexture(texture);

        SDL_RenderPresent(sdl.getRenderer());


        // //First clear the renderer
        // SDL_RenderClear(ren);
        // //Draw the texture
        // SDL_RenderCopy(ren, tex, NULL, NULL);
        // //Update the screen
        // SDL_RenderPresent(ren);
        // //Take a quick break after all that hard work

    }
    SDL_DestroyWindow(sdl.getWindow());
    SDL_Quit();
    return 0;
}