#include "Prototype.h"

void addIn(pileAction * pile, int index, int type){

    t_action * newAction = malloc(sizeof(t_action));
    t_action * cour;
    newAction->type=type;
    if(index==0 && pile->first!=NULL){
        newAction->suiv=pile->first;
        pile->first=newAction;
    }

    if(index>0 && pile->first!=NULL){
        cour = pile->first;
        while(index-1!=0){
            cour=cour->suiv;
            index--;
        }
        if(cour->suiv==NULL){
            cour->suiv=newAction;
            newAction->suiv=NULL;
        }
        else {
            newAction->suiv=cour->suiv;
            cour->suiv=newAction;
        }
    }

    if(pile->first==NULL){
        pile->first=newAction;
    }
}
