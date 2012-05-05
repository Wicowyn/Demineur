#include "prototype.h"
#include <SDL_ttf.h>
#define taille 17

void actualisationTableau(Eltab tab[][taille], SDL_Event event, bool &sortie, char &nb){
    int posx=2, posy=52, x=0, y=0;
    bool s=true, d=true;

    while(s & x<16){
        if(event.button.x>posx & event.button.x<posx+25) s=false;
        else{
            x++;
            posx+=27;}
    }
    while(d & y<16){
    if(event.button.y>posy & event.button.y<posy+25) d=false;
    else{
        y++;
        posy+=27;}
    }
    if(x!=16 & y!=16){
        switch(event.button.button){
            case SDL_BUTTON_LEFT:
                if(tab[x][y].val==0) clean(tab, x, y);
                tab[x][y].aff=true;
                tab[x][y].flag=false;
                if(tab[x][y].val==-1) sortie=false; break;
            case SDL_BUTTON_RIGHT:
                if(tab[x][y].aff==false){
                    if(tab[x][y].flag){
                        tab[x][y].flag=false;
                        nb++;}
                    else{
                        tab[x][y].flag=true;
                        nb--;}
                }break;
            default: ;}
    }
}

void createTableau(Eltab tab[][taille]){
    int posx=0, posy=0, x, y, i=0;
//    char xlim=2, ylim=2;

    while(i<40){
        posx=randNEW(0, 16);
        posy=randNEW(0, 16);
        if(tab[posx][posy].val!=-1){
            tab[posx][posy].val=-1;
            i++;
            x=posx-1;
            if(x==-1) x=0;
            y=posy-1;
            if(y==-1) y=0;

            while(y<posy+2){
                if(tab[x][y].val!=-1) tab[x][y].val++;
                x++;
                if(x==posx+2){
                    x=posx-1;
                    if(x==-1) x=0;
                    y++;}
            }
        }
    }
}

void actualisationMap(Eltab tab[][taille], int temp, SDL_Surface *fond, SDL_Surface *screen, SDL_Surface *bombe, SDL_Surface *masque, SDL_Surface *flag, char nbBombe){
    char x=0, y=0, num[3]={0};
    SDL_Surface *txt;
    SDL_Rect pos={0};
    SDL_Color black={0, 0 , 0}, red={255, 0, 0};
    TTF_Font *angelina=TTF_OpenFont("angelina.TTF", 25), *egoistism=TTF_OpenFont("d3egoistism.TTF", 50);

    SDL_BlitSurface(fond, NULL, screen, &pos);
    sprintf(num, "%d", nbBombe);
    txt=TTF_RenderUTF8_Blended(egoistism, num, red);
    SDL_BlitSurface(txt, NULL, screen, &pos);
    pos.x=300; pos.y=0;
    SDL_FreeSurface(txt);
    sprintf(num, "%d", temp);
    txt=TTF_RenderUTF8_Blended(egoistism, num, red);
    SDL_BlitSurface(txt, NULL, screen, &pos);
    pos.x=2; pos.y=52;

    while(y<16){
        if(tab[x][y].aff){
            if(tab[x][y].val==-1) SDL_BlitSurface(bombe, NULL, screen, &pos);
            if(tab[x][y].val>0){
                SDL_FreeSurface(txt);
                sprintf(num, " %d", tab[x][y].val);
                txt=TTF_RenderUTF8_Blended(angelina, num, black);
                SDL_BlitSurface(txt, NULL, screen, &pos);

            }
        }
        else{
            SDL_BlitSurface(masque, NULL, screen, &pos);
            if(tab[x][y].flag) SDL_BlitSurface(flag, NULL, screen, &pos);
        }
        pos.x+=27; //25+2
        x++;
        if(x==16){
            x=0;
            y++;
            pos.x=2;
            pos.y+=27;} //25+2
        }
    SDL_FreeSurface(txt);
    TTF_CloseFont(angelina);
    TTF_CloseFont(egoistism);
}

void clean(Eltab tab[][taille], char posx, char posy){
    char x=0, y=0, xx, yy;

    while(y<16){
        if(tab[x][y].val==0){
        if(seek(tab, x, y, posx, posy)==true){
            xx=x-1;
            if(xx==-1) xx=0;
            yy=y-1;
            if(yy==-1) yy=0;
            while(yy<y+2){
                tab[xx][yy].aff=true;
                tab[xx][yy].flag=false;
                xx++;
                if(xx==x+2){
                    xx=x-1;
                    if(xx==-1) xx=0;
                    yy++;}
            }
        }}
        x++;
        if(x==16){
            x=0;
            y++;}
    }
}

bool seek(Eltab tab[][taille], char x, char y, const char posx, const char posy){ // x&y pos actuel; posx&posy point a rejoindre;
    //bool s=true;
    char dirx, diry, difx=(x-posx), dify=(y-posy);

    if((x-posx)>0) dirx=-1;
    else{
        difx*=-1;
        if((x-posx)<0) dirx=1;
        else dirx=0;}
    if((y-posy)>0) diry=-1;
    else{
        dify*=-1;
        if((y-posy)<0) diry=1;
        else diry=0;}

    if(difx==0 & dify==0) return true;
    if((tab[x+dirx][y].val!=0 & tab[x][y+diry].val!=0) || (difx==0 & tab[x][y+diry].val!=0) || (dify==0 & tab[x+dirx][y].val!=0) || x==16 || x==-1 || y==16 || y==-1)  return false;

    if(difx>dify){
        if(tab[x+dirx][y].val==0) return seek(tab, x+dirx, y, posx, posy);
        else return seek(tab, x, y+diry, posx, posy);
    }
    else{
        if(tab[x][y+diry].val==0) return seek(tab, x, y+diry, posx, posy);
        else return seek(tab, x+dirx, y, posx, posy);
    }
}


