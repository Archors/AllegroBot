#ifndef GESTIONPILE_H_INCLUDED
#define GESTIONPILE_H_INCLUDED

void addIn(pileAction * pile, int index, int type);
void changeOrder(pileAction * pile, int fromIndex, int toIndex);
void readPile(t_personnage* bot, int numero, int **niv, int tailleX, int tailleY, int* tempo);
void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * spring);
int tailleliste(pileAction* pile);
void suppPile(pileAction* pile, int *cliquedrag, int *tempo);
void delAtIndex(pileAction * pile, int fromIndex);
void addToEnd(pileAction * pile, int type);
int readProc(t_personnage* bot, int numero, int **niv, int tailleX, int tailleY);
#endif
