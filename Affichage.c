#include "Prototype.h"

///Recois un tableau et affiche ce dernier
void MapCreation(int **tab, int taillex, int tailley,BITMAP *tampon, BITMAP *sol, BITMAP *tolight,BITMAP *light)
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
            if(tab[i][j] == 0) {}
            if(tab[i][j] == 1)
                masked_blit(sol,tampon,0,0,isox+400,isoy+100,sol->w,sol->h);
            if(tab[i][j] == 2)
                masked_blit(tolight,tampon,0,0,isox+400,isoy+100,tolight->w,tolight->h);
            if(tab[i][j] == 3)
                masked_blit(light,tampon,0,0,isox+400,isoy+100,light->w,light->h);
        }
    }
}

///Reception des sprites sur 1 image et decoupe en plusieurs images
void decoupage(BITMAP *base, BITMAP ***decoupe)
{
    int i;
    for(i=0; i<9; i++){
        blit(base,decoupe[0][i],(base->w/9)*i,(base->h)/8*0,0,0,decoupe[0][i]->w,decoupe[0][i]->h);
        blit(base,decoupe[1][i],(base->w/9)*i,(base->h)/8*2,0,0,decoupe[1][i]->w,decoupe[1][i]->h);
        blit(base,decoupe[2][i],(base->w/9)*i,(base->h)/8*5,0,0,decoupe[2][i]->w,decoupe[2][i]->h);
        blit(base,decoupe[3][i],(base->w/9)*i,(base->h)/8*7,0,0,decoupe[3][i]->w,decoupe[3][i]->h);
    }
}
