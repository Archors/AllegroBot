#ifndef GESTIONPILE_H_INCLUDED
#define GESTIONPILE_H_INCLUDED

typedef struct action
{
    int type;                   ///QUELLE ACTION CEST
    struct action * suiv;
} t_action;

typedef struct
{
    t_action * first;

} pileAction;

void addIn(pileAction * pile, int index, int type);
void changeOrder(pileAction * pile, int fromIndex, int toIndex);
void readPile(pileAction * pile, int * index,int x,int y, int *dirx, int *diry, int *dir, int **niv, int tailleX, int tailleY);

#endif
