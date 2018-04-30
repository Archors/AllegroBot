#include "Prototype.h"
#include "gestionPile.h"


void addIn(pileAction * pile, int index, int type)
{

    t_action * newAction = malloc(sizeof(t_action));
    t_action * cour;
    newAction->type=type;
    if(index==0 && pile->first!=NULL)
    {
        newAction->suiv=pile->first;
        pile->first=newAction;
    }

    if(index>0 && pile->first!=NULL)
    {
        cour = pile->first;
        while(index-1!=0)
        {
            cour=cour->suiv;
            index--;
        }
        if(cour->suiv==NULL)
        {
            cour->suiv=newAction;
            newAction->suiv=NULL;
        }
        else
        {
            newAction->suiv=cour->suiv;
            cour->suiv=newAction;
        }
    }

    if(pile->first==NULL)
    {
        pile->first=newAction;
    }
}

void changeOrder(pileAction * pile, int fromIndex, int toIndex)
{
    int type;
    t_action * cour=pile->first;
    t_action * prec=pile->first;
    while(fromIndex!=0)
    {
        prec=cour;
        cour=cour->suiv;
        fromIndex--;
    }
    type=cour->type;
    prec->suiv=cour->suiv;
    addIn(pile,toIndex,type);
    free(cour);
}

void readPile(pileAction * pile, int * index,int x,int y, int *dirx, int *diry, int *dir, int **niv, int tailleX, int tailleY)
{

    t_action * cour;
    while(index!=0)
    {
        if(cour->suiv!=NULL)
        {
            cour=cour->suiv;
            index--;
        }
        else
            break;
    }
    switch(cour->type)
    {
    case AVANCER :
        switch((*dir))
        {
        case UP :
            if(y-1>=0)
                if(niv[x][y]==niv[x][y-1])
                {
                    (*diry)--;
                }
            break;
        case LEFT :
            if(x-1>=0)
                if(niv[x][y]==niv[x-1][y])
                {
                    (*dirx)--;
                }
            break;
        case DOWN :
            if(y+1<tailleY)
                if(niv[x][y]==niv[x][y+1])
                {
                    (*diry)++;
                }
            break;
        case RIGHT :
            if(x+1<tailleX)
                if(niv[x][y]==niv[x+1][y])
                {
                    (*dirx)++;
                }
            break;
        default :
            break;
        }
        break;
    case JUMP :
        switch((*dir))
        {
        case UP :
            if(y-1>=0)
                if(niv[x][y-1]-niv[x][y]<2)
                {
                    (*diry)--;
                }
            break;
        case LEFT :
            if(x-1>=0)
                if(niv[x-1][y]-niv[x][y]<2)
                {
                    (*dirx)--;
                }
            break;
        case DOWN :
            if(y+1<tailleY)
                if(niv[x][y+1]-niv[x][y]<2)
                {
                    (*diry)++;
                }
            break;
        case RIGHT :
            if(x+1<tailleX)
                if(niv[x+1][y]-niv[x][y]<2)
                {
                    (*dirx)++;
                }
            break;
        default :
            break;
        }
        break;
    case LIGHT :
        if(niv[x][y]<10)
            niv[x][y]+=10;
        if(niv[x][y]>10)
            niv[x][y]-=10;
        break;
    case ROTATE_LEFT :
        if((*dir)==1)
        {
            (*dir)=4;
        }
        else
            (*dir)--;
        break;
    case ROTATE_RIGHT :
        if((*dir)==4)
        {
            (*dir)=1;
        }
        else
            (*dir)++;
        break;
    }
}
void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * spring)
{
    int cpt=1;
    t_action * cour=pile->first;
    if(cour!=NULL)
    {
        while(cour!=NULL)
        {
            switch(cour->type)
            {
            case AVANCER :
                draw_sprite(tampon,actionforward,802+(100*cpt),135+(100*(cpt%4)));
                break;
            case ROTATE_LEFT :
                draw_sprite(tampon,rotateleft,802+(100*cpt),135+(100*(cpt%4)));
                break;
            case ROTATE_RIGHT :
                draw_sprite(tampon,rotateright,802+(100*cpt),135+(100*(cpt%4)));
                break;
            case LIGHT :
                draw_sprite(tampon,actionlight,802+(100*cpt),135+(100*(cpt%4)));
                break;
            case JUMP :
                draw_sprite(tampon,spring,802+(100*cpt),135+(100*(cpt%4)));
                break;
            default:
                break;
            }
            cpt++;
            cour=cour->suiv;
        }
    }
}

