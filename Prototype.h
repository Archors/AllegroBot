#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>

typedef struct perso
{
    int x; ///Position en 2D
    int y;
    int isox; ///Position actuel en 2D isometrique
    int isoy;
    int dirx;
    int diry;
    int dirisox; ///Position en 2D isometrique
    int dirisoy;
    int direction;
    BITMAP ***sprite;
} t_personnage;

void MapCreation(int **tab, int taillex, int tailley,int decalx, int decaly,BITMAP *tampon, BITMAP *sol,BITMAP *tolight, BITMAP *light);
void decoupage(BITMAP *base, BITMAP ***decoupe);
void liberer(int **map, t_personnage *bot, int taillex);
void initalleg();
void deplacement(t_personnage *personnage, int vitesse);
void draganddrop(BITMAP* tampon, BITMAP* forward, BITMAP* light, BITMAP* left, BITMAP* right,BITMAP* spring, int *mem, int action[5], int *cliquedrag);
int toisox(int x, int y);
int toisoy(int x, int y);

#endif // PROTOTYPE_H_INCLUDED
