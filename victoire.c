#include "Prototype.h"
#include "gestionPile.h"

int finlvl(int** map, int taillex, int tailley)
{
    int i=0,j=0;
    for(i=0; i<taillex; i++)
        for(j=0; j<tailley; j++)
            if(map[i][j] == 2)
                return 0;
    return 1;
}

void changelvl(t_personnage *bot,int* lvl, int** map,int taillex, int tailley, int *play,int *tempo)
{
    int i=0;
    if(finlvl(map,taillex,tailley))
    {
        *play=0;
        *tempo=0;
        (*lvl)++;
        if(*lvl == 1)
            lvl1(bot,map);
        if(*lvl == 2)
            lvl2(bot,map);
        if(*lvl == 3)
            lvl3(bot,map);
        if(*lvl == 4)
            lvl4(bot,map);
        resetbot(bot);
        listfree(bot[i].themain);
        listfree(bot[i].proc);
    }
}

void listfree(pileAction* list)
{
    while(tailleliste(list))
    {
        delAtIndex(list,0);
    }
}

void lvl1(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=2;
    bot[0].y=2;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].active=1;
    bot[0].direction=RIGHT;
    bot[1].x=5;
    bot[1].y=0;
    bot[1].dirx=5;
    bot[1].diry=0;
    bot[1].active=0;
    bot[2].x=0;
    bot[2].y=5;
    bot[2].dirx=0;
    bot[2].diry=5;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=1;

}

void lvl2(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].active=1;
    bot[0].direction=RIGHT;
    bot[1].x=5;
    bot[1].y=0;
    bot[1].dirx=5;
    bot[1].diry=0;
    bot[1].active=0;
    bot[2].x=0;
    bot[2].y=5;
    bot[2].dirx=0;
    bot[2].diry=5;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=1;
    map[0][0] = 1;
    map[3][3] = 1;
    map[2][2] = 2;
}

void lvl3(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].active=1;
    bot[0].direction=RIGHT;
    bot[1].x=5;
    bot[1].y=0;
    bot[1].dirx=5;
    bot[1].diry=0;
    bot[1].active=0;
    bot[2].x=0;
    bot[2].y=5;
    bot[2].dirx=0;
    bot[2].diry=0;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=0;
    for(i=0; i<5; i++)
        map[i][0]=2;
}

void lvl4(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].active=1;
    bot[0].direction=RIGHT;
    bot[1].x=5;
    bot[1].y=0;
    bot[1].dirx=5;
    bot[1].diry=0;
    bot[1].active=0;
    bot[2].x=0;
    bot[2].y=5;
    bot[2].dirx=0;
    bot[2].diry=0;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=0;
    map[3][3] = 2;
    map[4][4] = 2;
}

void resetbot(t_personnage* bot)
{
    int i=0;
    for(i=0; i<5; i++)
    {
        bot[i].actuelsprite=8;
        bot[i].compteur=0;
        bot[i].index=0;
        bot[i].cpt=0;
        bot[i].cptProc=0;
        bot[i].isox=toisox(bot[i].dirx,bot[i].diry);
        bot[i].isoy=toisoy(bot[i].dirx,bot[i].diry);
        bot[i].dirisox=toisox(bot[i].dirx,bot[i].diry);
        bot[i].dirisoy=toisoy(bot[i].dirx,bot[i].diry);
    }
}
