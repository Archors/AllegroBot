#include "Prototype.h"
#include "gestionPile.h"


void addIn(pileAction * pile, int index, int type)
{
    if(index < 20)
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

void readPile(t_personnage* bot, int numero, int **niv, int tailleX, int tailleY, int* tempo)
{
    static int isProcActive[5]= {0};
    static int actionCpt[5]= {0};
    int cpt=actionCpt[numero];
    if(cpt<=bot[numero].compteur)
    {
        if(isProcActive[numero]==0)
        {
            t_action * cour= (bot[numero].themain)->first;
            while(cpt!=0)
            {
                if(cour->suiv!=NULL)
                {
                    cour=cour->suiv;
                    cpt--;
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
                        (bot[numero].diry)--;
                    break;
                case LEFT :
                    if(bot[numero].x-1>=0)
                        (bot[numero].dirx)--;

                    break;
                case DOWN :
                    if(bot[numero].y+1<tailleY)
                        (bot[numero].diry)++;

                    break;
                case RIGHT :
                    if(bot[numero].x+1<tailleX)
                        (bot[numero].dirx)++;
                    break;
                default :
                    break;
                }
                break;
            case JUMP :
                switch((bot[numero].direction))
                {
                case UP :
                    if(bot[numero].y-1>=0)
                        if(niv[bot[numero].x][bot[numero].y-1]-niv[bot[numero].x][bot[numero].y]<2)
                            (bot[numero].direction)--;
                    break;
                case LEFT :
                    if(bot[numero].x-1>=0)
                        if(niv[bot[numero].x-1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                            (bot[numero].direction)--;
                    break;
                case DOWN :
                    if(bot[numero].y+1<tailleY)
                        if(niv[bot[numero].x][bot[numero].y+1]-niv[bot[numero].x][bot[numero].y]<2)
                            (bot[numero].direction)++;
                    break;
                case RIGHT :
                    if(bot[numero].x+1<tailleX)
                        if(niv[bot[numero].x+1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                            (bot[numero].direction)++;
                    break;
                default :
                    break;
                }
                break;
            case LIGHT :
                if(niv[bot[numero].x][bot[numero].y] == 2)
                    niv[bot[numero].x][bot[numero].y] = 3;
                else if(niv[bot[numero].x][bot[numero].y] == 3)
                    niv[bot[numero].x][bot[numero].y] = 2;
                break;
            case ROTATE_LEFT :
                if(bot[numero].direction == LEFT)
                    bot[numero].direction = DOWN;
                else if(bot[numero].direction == DOWN)
                    bot[numero].direction = RIGHT;
                else if(bot[numero].direction == RIGHT)
                    bot[numero].direction = UP;
                else if(bot[numero].direction == UP)
                    bot[numero].direction = LEFT;
                break;
            case ROTATE_RIGHT :
                if(bot[numero].direction == DOWN)
                    bot[numero].direction = LEFT;
                else if(bot[numero].direction == RIGHT)
                    bot[numero].direction = DOWN;
                else if(bot[numero].direction == UP)
                    bot[numero].direction = RIGHT;
                else if(bot[numero].direction == LEFT)
                    bot[numero].direction = UP;
                break;
            case PROC :
                isProcActive[numero]=1;
                break;
            }
            actionCpt[numero]++;
        }
        else
            isProcActive[numero]=readProc(bot,numero,niv,tailleX,tailleY);
        *tempo=30;
    }
}

int readProc(t_personnage* bot, int numero, int **niv, int tailleX, int tailleY)
{
    static int actionCpt[5]= {0};
    t_action * cour = (bot[numero].proc)->first;
    int cpt = actionCpt[numero];
    if(cour==NULL)
        return 0;
    while(cpt!=0)
    {
        if(cour->suiv!=NULL)
        {
            cour=cour->suiv;
            cpt--;
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
                    (bot[numero].direction)--;
                }
            break;
        case LEFT :
            if(bot[numero].x-1>=0)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x-1][bot[numero].y])
                {
                    (bot[numero].direction)--;
                }
            break;
        case DOWN :
            if(bot[numero].y+1<tailleY)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x][bot[numero].y+1])
                {
                    (bot[numero].direction)++;
                }
            break;
        case RIGHT :
            if(bot[numero].x+1<tailleX)
                if(niv[bot[numero].x][bot[numero].y]==niv[bot[numero].x+1][bot[numero].y])
                {
                    (bot[numero].direction)++;
                }
            break;
        default :
            break;
        }
        break;
    case JUMP :
        switch((bot[numero].direction))
        {
        case UP :
            if(bot[numero].y-1>=0)
                if(niv[bot[numero].x][bot[numero].y-1]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    (bot[numero].direction)--;
                }
            break;
        case LEFT :
            if(bot[numero].x-1>=0)
                if(niv[bot[numero].x-1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    (bot[numero].direction)--;
                }
            break;
        case DOWN :
            if(bot[numero].y+1<tailleY)
                if(niv[bot[numero].x][bot[numero].y+1]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    (bot[numero].direction)++;
                }
            break;
        case RIGHT :
            if(bot[numero].x+1<tailleX)
                if(niv[bot[numero].x+1][bot[numero].y]-niv[bot[numero].x][bot[numero].y]<2)
                {
                    (bot[numero].direction)++;
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
        if((bot[numero].direction)==1)
        {
            (bot[numero].direction)=4;
        }
        else
            (bot[numero].direction)--;
        break;
    case ROTATE_RIGHT :
        if((bot[numero].direction)==4)
        {
            (bot[numero].direction)=1;
        }
        else
            (bot[numero].direction)++;
        break;
    }
    bot[numero].dirisox=toisox(bot[numero].dirx,bot[numero].diry);
    bot[numero].dirisoy=toisox(bot[numero].x,bot[numero].y);
    actionCpt[numero]++;
    if(cour->suiv==NULL)
        return 0;
    else
        return 1;
}


void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * spring)
{
    int cpt=0;
    int row=0;
    int nb=0;
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
            nb++;
        }
    }
}

void suppPile(pileAction* pile, int *cliquedrag, int *tempo)
{
    int cpt=0;
    int row=0;
    int nb=0;
    t_action * cour=pile->first;
    (*tempo)--;
    if(cour!=NULL && *tempo < 0)
    {
        while(cour!=NULL)
        {
            if(*cliquedrag != 1 && mouse_b&1 && mouse_x > 805+(100*cpt) && mouse_x < 905+(100*cpt) && mouse_y > 150+(100*row) && mouse_y < 250+(100*row))
            {
                delAtIndex(pile,nb);
                *tempo=5;
                break;
            }
            cpt++;
            if(cpt==4)
            {
                row++;
                cpt=0;
            }
            cour=cour->suiv;
            nb++;
        }
    }
}

int tailleliste(pileAction* pile)
{
    if(pile->first == NULL)
        return 0;
    int taille=0;
    t_action *tempo=pile->first;
    while(tempo != NULL)
    {
        tempo=tempo->suiv;
        taille++;
    }
    return taille;
}

void addToEnd(pileAction * pile, int type)
{
    t_action * cour=pile->first;
    int index=0;
    if(cour == NULL)
    {
        addIn(pile,0,type);
        return;
    }
    else
    {
        while(cour!=NULL)
        {
            cour=cour->suiv;
            index++;
        }
        addIn(pile,index,type);
    }
}

void delAtIndex(pileAction * pile, int fromIndex)
{
    if(fromIndex==0)
    {
        t_action * cour=pile->first;
        pile->first=cour->suiv;
        free(cour);
    }
    else
    {
        t_action * cour=pile->first;
        t_action * prec=pile->first;
        while(fromIndex!=0)
        {
            prec=cour;
            cour=cour->suiv;
            fromIndex--;
        }
        prec->suiv=cour->suiv;
        free(cour);
    }
}
