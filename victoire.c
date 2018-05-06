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
        bot[i].compteur=0;
        bot[i].index=0;
        bot[0].cpt=0;
        *tempo=0;
        (*lvl)++;
        if(*lvl == 1)
        {
            bot[i].direction=RIGHT;
            bot[i].dirx=0;
            bot[i].diry=0;
            bot[i].dirisox=0;
            bot[i].dirisoy=0;
            *play = 0;
        }
        if(*lvl == 2)
        {
            bot[i].direction=RIGHT;
            bot[i].dirx=0;
            bot[i].diry=0;
            bot[i].dirisox=0;
            bot[i].dirisoy=0;
            *play = 0;
            map[0][0] = 1;
            map[3][3] = 1;
            map[2][2] = 2;
        }
        if(*lvl == 3)
        {
            /**/
        }
        if(*lvl == 4)
        {
            /**/
        }
        listfree(bot[i].themain);
    }
}

void listfree(pileAction* list)
{
    while(tailleliste(list))
    {
        delAtIndex(list,0);
    }
}
