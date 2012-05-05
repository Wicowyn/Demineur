#include "Proto_CallBack.h"
#include <SDL_ttf.h>
#include <SDL/SDL.h>



Uint32 ttime(Uint32 intervalle, void *para){
    SDL_Surface *txt;
    SDL_Color red={255, 0, 0};
    SDL_Rect pos;
    char temp[3];

    Time *point;
    point=static_cast<Time*>(para); //permet de résoudre le probléme de conversion void->Time en C++
    pos.x=350; pos.y=0;
    point->temp++;
    sprintf(temp, "%d", point->temp);
    txt=TTF_RenderUTF8_Blended(TTF_OpenFont("d3egoistism.TTF", 50), temp, red);
    SDL_BlitSurface(txt, NULL, point->screen, &pos);
    SDL_Flip(point->screen);

    return intervalle;
}

