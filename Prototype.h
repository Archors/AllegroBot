#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
#define AVANCER 1
#define LIGHT 2
#define ROTATE_LEFT 3
#define ROTATE_RIGHT 4
#define PROC 5
#define LEFT 0
#define UP 1
#define DOWN 2
#define RIGHT 3



typedef struct action
{
    int type;                   ///QUELLE ACTION CEST
    struct action * suiv;
} t_action;

typedef struct
{
    t_action * first;

} pileAction;

typedef struct perso
{
    int active;
    int x; ///Position en 2D
    int y;
    int isox; ///Position actuel en 2D isometrique
    int isoy;
    int dirx;
    int diry;
    int dirisox; ///Position en 2D isometrique
    int dirisoy;
    int direction;
    int index;
    int compteur;
    int cpt; ///Variable de la liste d'action
    int cptProc; ///Variable de la liste d'action
    int actuelsprite;
    pileAction* themain;
    pileAction* proc;
    BITMAP ***sprite;
} t_personnage;


void MapCreation(int **tab, int taillex, int tailley,int decalx, int decaly,BITMAP *tampon, BITMAP *sol,BITMAP *tolight, BITMAP *light);
void decoupage(BITMAP *base, BITMAP ***decoupe);
void liberer(int **map, t_personnage *bot, int taillex);
void initalleg();
void deplacement(t_personnage *personnage, int vitesse);
void draganddrop(t_personnage* bot,int* boolmain, BITMAP* tampon, BITMAP* forward, BITMAP* light, BITMAP* left, BITMAP* right,BITMAP* spring, int *mem, int action[5], int *cliquedrag);
int toisox(int x, int y);
int toisoy(int x, int y);
void addIn(pileAction * pile, int index, int type);
void bouton(BITMAP* tampon, BITMAP* jouer, BITMAP* stop, int *play, int *tempo);
void drag(pileAction* pile, int *cliquedrag,int *mem);
void affsprite(t_personnage* bot,BITMAP* tampon,int decalx, int decaly);
void clique(pileAction *pile, int action[5],int *clique);
void changelvl(t_personnage *bot,int* lvl, int** map,int taillex, int tailley, int *play, int *tempo);
void mainproc(int *booleen,BITMAP* tampon, BITMAP *main, BITMAP *proc);

#endif // PROTOTYPE_H_INCLUDED
