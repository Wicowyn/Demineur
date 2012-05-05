#include "prototype.h"
//#include "Proto_CallBack.h"
#define taille 17

int randNEW(int a, int b){   //génére un nombre pseudo-aléatoire entre a(inclus) et b(exclu)
    return (rand()%(b-a)+a);
}


int main ( int argc, char** argv )
{
    SDL_Surface *screen, *bombe, *bdnH, *bdnV, *fond, *cache, *flag;
    SDL_Rect po={0};
    SDL_Event event;
    SDL_Color red={255, 0, 0};
    //SDL_TimerID timer;
    Eltab stab[taille][taille]={0};
    bool s=true, d=true;
    char nbBombe=40, x=0, y=0;
    int tmp_av=0, tmp_mn=SDL_GetTicks(), tim=0;
    //Time point={0};

    //point.screen=screen;

    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    //timer=SDL_AddTimer(1000, ttime, &point);
    screen=SDL_SetVideoMode(434, 484, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Demineur", NULL);
    bombe=IMG_Load("bombe.png");
    SDL_SetColorKey(bombe, SDL_SRCCOLORKEY, SDL_MapRGB(bombe->format, 255, 255, 255));
    cache=IMG_Load("cache.png");
    SDL_SetColorKey(cache, SDL_SRCCOLORKEY, SDL_MapRGB(cache->format, 255, 255, 255));
    flag=IMG_Load("flag.png");
    SDL_SetColorKey(flag, SDL_SRCCOLORKEY, SDL_MapRGB(flag->format, 255, 255, 255));
    fond=SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, 434, 484, 32, 0, 0, 0, 0);
    SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 255, 255, 255));
    bdnH=SDL_CreateRGBSurface(NULL, 434, 2, 32, 0, 0, 0, 0);
    bdnV=SDL_CreateRGBSurface(NULL, 2, 434, 32, 0, 0, 0, 0);

    for(po.x=0, po.y=50; po.x<=432; po.x+=27) SDL_BlitSurface(bdnV, NULL, fond, &po);
    for(po.x=0, po.y=50; po.y<=482; po.y+=27) SDL_BlitSurface(bdnH, NULL, fond, &po);

    createTableau(stab);
    actualisationMap(stab, tim/40, fond, screen, bombe, cache, flag, nbBombe);
    SDL_Flip(screen);

    while(s){
        tmp_mn=SDL_GetTicks();
        if((tmp_mn-tmp_av)>25){
            tmp_av=tmp_mn;
            tim++;
            SDL_PollEvent(&event);
            switch(event.type){
                case SDL_QUIT: s=false; break;
                case SDL_KEYDOWN: if(event.key.keysym.sym==SDLK_ESCAPE) s=false; break;
                case SDL_MOUSEBUTTONUP: actualisationTableau(stab, event, s, nbBombe);
                    event={0}; break;
                default: ;
            }
            actualisationMap(stab, tim/40, fond, screen, bombe, cache, flag, nbBombe);
            SDL_Flip(screen);
        }
        else SDL_Delay(25-(tmp_mn-tmp_av));
    }

    while(y<16){
        if(stab[x][y].val==-1){
            stab[x][y].aff=true;
            stab[x][y].flag=false;}
        x++;
        if(x==16){
            x=0;
            y++;}
        }
    actualisationMap(stab, tim/40, fond, screen, bombe, cache, flag, nbBombe);
    SDL_Flip(screen);
    SDL_Delay(500);
    while(d){
        SDL_WaitEvent(&event);
        if(event.type==SDL_QUIT || (event.type==SDL_KEYDOWN & event.key.keysym.sym==SDLK_RETURN)) d=false;
    }
    SDL_FreeSurface(flag);
    SDL_FreeSurface(bombe);
    SDL_FreeSurface(bdnH);
    SDL_FreeSurface(bdnV);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(cache);
    SDL_FreeSurface(screen);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
