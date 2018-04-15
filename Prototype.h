#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

typedef struct perso
{
    int x;
    int y;
    int isox;
    int isoy;
    int direction;
    BITMAP ***sprite;
}t_personnage;

void MapCreation(int **tab, int taillex, int tailley,BITMAP *tampon, BITMAP *sol,BITMAP *tolight, BITMAP *light);
void decoupage(BITMAP *base, BITMAP ***decoupe);
void liberer(int **map, t_personnage *bot);

#endif // PROTOTYPE_H_INCLUDED
