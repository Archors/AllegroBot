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

void bouton(BITMAP* tampon, BITMAP* jouer, BITMAP* stop, int *play, int *tempo)
{
    if(tempo > 0)
        (*tempo)--;
    if(*play == 0)
        draw_sprite(tampon,jouer,800,20); ///Affichage du bouton pour lancer la compilation
    if(*play == 1)
        draw_sprite(tampon,stop,800,20);
    if(mouse_b&1 && mouse_x > 800 && mouse_y > 20 && mouse_x < 800 + jouer->w && mouse_y < 20 + jouer->h && *tempo < 0)
    {
        if(*play==0)
        {
            *play=1;
            *tempo = 13;
        }
        else
        {
            *play=0;
            *tempo=13;
        }
    }
}

void affsprite(t_personnage* bot,BITMAP* tampon,int decalx, int decaly)
{
    int i=0;
    //for(i=0; i<5; i++)
    switch (bot[i].direction)
    {
    case UP:
        draw_sprite(tampon, bot[i].sprite[UP][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[0].isoy+decaly-10);
        break;
    case DOWN:
        draw_sprite(tampon, bot[i].sprite[DOWN][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[0].isoy+decaly-10);
        break;
    case LEFT:
        draw_sprite(tampon, bot[i].sprite[LEFT][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[0].isoy+decaly-10);
        break;
    case RIGHT:
        draw_sprite(tampon, bot[i].sprite[RIGHT][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[0].isoy+decaly-10);
        break;
    }
    if(bot[i].isox == bot[i].dirisox && bot[i].isoy == bot[i].dirisoy)
        bot[i].actuelsprite=8;
    else
    {
        bot[i].actuelsprite--;
        if(bot[i].actuelsprite < 0)
            bot[i].actuelsprite = 8;
    }
}
