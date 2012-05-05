#include <SDL/SDL.h>
#include <time.h>

typedef struct{
    SDL_Surface* screen;
    int temp;
}Time;

Uint32 ttime(Uint32 intervalle, void*);

