#include "Prototype.h"

///Recois un tableau et affiche ce dernier
void MapCreation(int **tab, int taillex, int tailley,int decalx, int decaly,BITMAP *tampon, BITMAP *sol, BITMAP *tolight,BITMAP *light)
{
    int i=0,j=0; ///Parcourt du tableau de la map
    int x,y; ///Position cartesienne de depart
    int isox,isoy; ///Variable de conversion de cartesion à 2D isometrique
    ///Parcours du tableau
    for(i=0; i<taillex; i++)
    {
        for(j=0; j<tailley; j++)
        {
            x=j*74;
            y=i*74;
            isox=x-y;
            isoy=(x+y)/2;
            switch (tab[i][j])
            {
            case 1 :
                masked_blit(sol,tampon,0,0,isox+decalx,isoy+decaly,sol->w,sol->h);
                break;
            case 2 :
                masked_blit(tolight,tampon,0,0,isox+decalx,isoy+decaly,tolight->w,tolight->h);
                break;
            case 3 :
                masked_blit(light,tampon,0,0,isox+decalx,isoy+decaly,light->w,light->h);
                break;
            }
        }
    }
}


///Reception des sprites sur 1 image et decoupe en plusieurs images
void decoupage(BITMAP *base, BITMAP ***decoupe)
{
    int i;
    for(i=0; i<9; i++)
    {
        blit(base,decoupe[0][i],(base->w/9)*i,(base->h)/8*0,0,0,decoupe[0][i]->w,decoupe[0][i]->h);
        blit(base,decoupe[1][i],(base->w/9)*i,(base->h)/8*2,0,0,decoupe[1][i]->w,decoupe[1][i]->h);
        blit(base,decoupe[2][i],(base->w/9)*i,(base->h)/8*5,0,0,decoupe[2][i]->w,decoupe[2][i]->h);
        blit(base,decoupe[3][i],(base->w/9)*i,(base->h)/8*7,0,0,decoupe[3][i]->w,decoupe[3][i]->h);
    }
}

int toisox(int x, int y)
{
    return(x*74-y*74);
}

int toisoy(int x, int y)
{
    return((x*74+y*74)/2);
}

void deplacement(t_personnage *bot, int vitesse)
{
    int i=0;
    bot[i].isox += (bot[i].dirisox - bot[i].isox) * vitesse / (sqrt((bot[i].isox - bot[i].dirisox)*(bot[i].isox - bot[i].dirisox) + (bot[i].isoy - bot[i].dirisoy)*(bot[i].isoy - bot[i].dirisoy)));
    bot[i].isoy += (bot[i].dirisoy - bot[i].isoy) * vitesse / (sqrt((bot[i].isox - bot[i].dirisox)*(bot[i].isox - bot[i].dirisox) + (bot[i].isoy - bot[i].dirisoy)*(bot[i].isoy - bot[i].dirisoy)));
    if(bot[i].isox < 10+bot[i].dirisox && bot[i].isoy < 10+bot[i].dirisoy  && bot[i].isox > bot[i].dirisox-10 && bot[i].isoy > bot[i].dirisoy-10)
    {
        bot[i].isox=bot[i].dirisox;
        bot[i].isoy=bot[i].dirisoy;
    }
}
