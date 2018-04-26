#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
#define AVANCER 1
#define LIGHT 2
#define ROTATELEFT 3
#define ROTATERIGHT 4
#define SPRING 5

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
}t_personnage;

void MapCreation(int **tab, int taillex, int tailley,int decalx, int decaly,BITMAP *tampon, BITMAP *sol,BITMAP *tolight, BITMAP *light);
void decoupage(BITMAP *base, BITMAP ***decoupe);
void liberer(int **map, t_personnage *bot, int taillex);
void initalleg();
void deplacement(t_personnage *personnage, int vitesse);
int toisox(int x, int y);
int toisoy(int x, int y);

#endif // PROTOTYPE_H_INCLUDED
