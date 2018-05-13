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
    if(finlvl(map,taillex,tailley)==1)
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
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].direction=RIGHT;
    bot[1].x=4;
    bot[1].y=1;
    bot[1].dirx=4;
    bot[1].diry=1;
    bot[1].direction=RIGHT;
    bot[2].x=0;
    bot[2].y=3;
    bot[2].dirx=1;
    bot[2].diry=1;
    bot[2].direction=UP;
    bot[3].x=1;
    bot[3].y=3;
    bot[3].dirx=1;
    bot[3].diry=3;
    bot[3].direction=DOWN;
    bot[4].x=3;
    bot[4].y=2;
    bot[4].dirx=3;
    bot[4].diry=2;
    bot[4].direction=RIGHT;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=1;
    map[3][3]=2;
}

void lvl2(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].direction=RIGHT;
    bot[1].x=4;
    bot[1].y=1;
    bot[1].dirx=4;
    bot[1].diry=1;
    bot[1].direction=LEFT;
    bot[2].x=0;
    bot[2].y=4;
    bot[2].dirx=0;
    bot[2].diry=4;
    bot[2].direction=UP;
    bot[3].x=4;
    bot[3].y=4;
    bot[3].dirx=4;
    bot[3].diry=4;
    bot[3].direction=RIGHT;
    bot[4].x=3;
    bot[4].y=3;
    bot[4].dirx=3;
    bot[4].diry=3;
    bot[4].direction=LEFT;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=1;
    map[0][0] = 2;
    map[3][3] = 2;
    map[2][2] = 2;
}

void lvl3(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].direction=RIGHT;
    bot[1].x=4;
    bot[1].y=0;
    bot[1].dirx=4;
    bot[1].diry=0;
    bot[1].direction=DOWN;
    bot[2].x=0;
    bot[2].y=4;
    bot[2].dirx=0;
    bot[2].diry=4;
    bot[2].direction=UP;
    bot[3].x=4;
    bot[3].y=4;
    bot[3].dirx=4;
    bot[3].diry=4;
    bot[3].direction=LEFT;
    bot[4].x=2;
    bot[4].y=2;
    bot[4].dirx=2;
    bot[4].diry=2;
    bot[4].direction=LEFT;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=1;
    for(i=0; i<5; i++)
    {
        map[i][0]=2;
        map[0][i]=2;
        map[4][i]=2;
        map[i][4]=2;
    }

    map[0][2]=0;
    map[2][0]=0;
    map[4][2]=0;
    map[2][4]=0;
}

void lvl4(t_personnage* bot, int** map)
{
    int i=0,j=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].direction=RIGHT;
    bot[1].x=0;
    bot[1].y=1;
    bot[1].dirx=0;
    bot[1].diry=1;
    bot[1].direction=RIGHT;
    bot[2].x=0;
    bot[2].y=2;
    bot[2].dirx=0;
    bot[2].diry=2;
    bot[2].direction=RIGHT;
    bot[3].x=0;
    bot[3].y=3;
    bot[3].dirx=0;
    bot[3].diry=3;
    bot[3].direction=RIGHT;
    bot[4].x=0;
    bot[4].y=4;
    bot[4].dirx=0;
    bot[4].diry=4;
    bot[4].direction=RIGHT;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            map[i][j]=2;
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
