#include <cstdlib>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <iostream>
#define taille 17

struct Eltab{
    int val;
    bool aff;
    bool flag;
};

int randNEW(int a, int b);
void actualisationTableau(Eltab tab[][taille], SDL_Event, bool&, char&);
void createTableau(Eltab tab[][taille]);
void actualisationMap(Eltab tab[][taille], int, SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Surface*, char);
void clean(Eltab tab[][taille], char, char);
bool seek(Eltab tab[0][taille], char, char, const char, const char);
