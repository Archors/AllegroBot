#ifndef GESTIONPILE_H_INCLUDED
#define GESTIONPILE_H_INCLUDED

void addIn(pileAction * pile, int index, int type);
void changeOrder(pileAction * pile, int fromIndex, int toIndex);
void readPile(pileAction * pile, int * index,int x,int y, int *dirx, int *diry, int *dir, int **niv, int tailleX, int tailleY);
void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * spring);

#endif
