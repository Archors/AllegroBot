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

void readPile(t_personnage* bot,int numero, int **niv, int tailleX, int tailleY)
{

    t_action * cour;
    while(bot[numero].compteur!=0)
    {
        if(cour->suiv!=NULL)
        {
            cour=cour->suiv;
            bot[numero].compteur--;
        }
        else
            break;
    }
    switch(cour->type)
    {
    case AVANCER :
        switch((bot[numero].direction))
        {
        case UP :
            if(bot[numero].y-1>=0)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x][bot[numero].y-1])
                {
                    bot[numero].direction--;
                }
            break;
        case LEFT :
            if(bot[numero].x-1>=0)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x-1][bot[numero].y])
                {
                    bot[numero].direction--;
                }
            break;
        case DOWN :
            if(bot[numero].y+1<tailleY)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x][bot[numero].y+1])
                {
                    bot[numero].direction++;
                }
            break;
        case RIGHT :
            if(bot[numero].x+1<tailleX)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x+1][bot[numero].y])
                {
                    bot[numero].direction++;
                }
            break;
        default :
            break;
        }
        break;
    case JUMP :
        switch(bot[numero].direction)
        {
        case UP :
            if(bot[numero].y-1>=0)
                if(niv[bot[numero].x][bot[numero].y-1]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    bot[numero].direction--;
                }
            break;
        case LEFT :
            if(bot[numero].x-1>=0)
                if(niv[bot[numero].x-1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    bot[numero].direction--;
                }
            break;
        case DOWN :
            if(bot[numero].y+1<tailleY)
                if(niv[bot[numero].x][bot[numero].y+1]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    bot[numero].direction++;
                }
            break;
        case RIGHT :
            if(bot[numero].x+1<tailleX)
                if(niv[bot[numero].x+1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    bot[numero].direction++;
                }
            break;
        default :
            break;
        }
        break;
    case LIGHT :
        if(niv[bot[numero].x][bot[numero].y]<10)
            niv[bot[numero].x][bot[numero].y]+=10;
        if(niv[bot[numero].x][bot[numero].y]>10)
            niv[bot[numero].x][bot[numero].y]-=10;
        break;
    case ROTATE_LEFT :
        if(bot[numero].direction==1)
        {
            bot[numero].direction=4;
        }
        else
            bot[numero].direction--;
        break;
    case ROTATE_RIGHT :
        if(bot[numero].direction==4)
        {
            bot[numero].direction=1;
        }
        else
            bot[numero].direction++;
        break;
    }
}
void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * spring)
{
    int cpt=0;
    int row=0;
    t_action * cour=pile->first;
    if(cour!=NULL)
    {
        while(cour!=NULL)
        {
            switch(cour->type)
            {
            case AVANCER :
                draw_sprite(tampon,actionforward,805+(100*cpt),150+(100*row));
                break;
            case ROTATE_LEFT :
                draw_sprite(tampon,rotateleft,805+(100*cpt),150+(100*row));
                break;
            case ROTATE_RIGHT :
                draw_sprite(tampon,rotateright,805+(100*cpt),150+(100*row));
                break;
            case LIGHT :
                draw_sprite(tampon,actionlight,805+(100*cpt),150+(100*row));
                break;
            case JUMP :
                draw_sprite(tampon,spring,805+(100*cpt),150+(100*row));
                break;
            default:
                break;
            }
            cpt++;
            if(cpt==4)
            {
                row++;
                cpt=0;
            }
            cour=cour->suiv;
        }
    }
}

