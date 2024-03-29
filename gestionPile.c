#include "Prototype.h"
#include "gestionPile.h"


void addIn(pileAction * pile, int index, int type)
{
    if(index < 20)
    {
        t_action * newAction = calloc(1,sizeof(t_action));
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

void readPile(t_personnage* bot, int **niv, int tailleX, int tailleY, int* tempo)
{
    static int isProcActive[5]= {0};
    int numero=0;
    int cpt=bot[0].cpt;
    int end =0;
    if(isProcActive[numero]==0)
    {
        t_action * cour= (bot[0].themain)->first;
        while(cpt!=0)
        {
            if(cour->suiv!=NULL)
            {
                cour=cour->suiv;
                cpt--;
            }
            else
            {
                end=1;
                break;
            }
        }
        if(end==0)
        {
            numero=0;
            for(numero=0; numero<5; numero++)
            {
                if(bot[numero].active)
                {
                    switch(cour->type)
                    {
                    case AVANCER :
                        switch((bot[numero].direction))
                        {
                        case UP :
                            if(bot[numero].diry > 0)
                                if(niv[bot[numero].diry-1][bot[numero].dirx]>0)
                                    (bot[numero].diry)--;
                            break;
                        case LEFT :
                            if(bot[numero].dirx > 0)
                                if(niv[bot[numero].diry][bot[numero].dirx-1]>0)
                                    (bot[numero].dirx)--;

                            break;
                        case DOWN :
                            if(bot[numero].diry < 4)
                                if(niv[bot[numero].diry+1][bot[numero].dirx]>0)
                                    (bot[numero].diry)++;

                            break;
                        case RIGHT :
                            if(bot[numero].dirx < 4)
                                if(niv[bot[numero].diry][bot[numero].dirx+1]>0)
                                    (bot[numero].dirx)++;
                            break;
                        default :
                            break;
                        }
                        break;
                    case LIGHT :
                        if(niv[bot[numero].diry][bot[numero].dirx] == 2)
                            niv[bot[numero].diry][bot[numero].dirx] = 3;
                        else if(niv[bot[numero].diry][bot[numero].dirx] == 3)
                            niv[bot[numero].diry][bot[numero].dirx] = 2;
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
                }
            }
            bot[0].cpt++;
        }
    }
    else
    {
        isProcActive[0]=readProc(bot,niv,tailleX,tailleY);
        if(isProcActive[0]==0)
        {
            bot[0].cptProc=0;
        }
    }
    *tempo=30;
}

int readProc(t_personnage* bot, int **niv, int tailleX, int tailleY)
{
    t_action * cour = (bot[0].proc)->first;
    int numero=0;
    if(cour==NULL)
        return 0;
    int cpt = bot[0].cptProc;
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
    for(numero=0; numero<5; numero++)
    {
        if(bot[numero].active)
        {
            switch(cour->type)
            {
            case AVANCER :
                switch((bot[numero].direction))
                {
                case UP :
                    if(bot[numero].diry > 0)
                        if(niv[bot[numero].diry-1][bot[numero].dirx]>0)
                            (bot[numero].diry)--;
                    break;
                case LEFT :
                    if(bot[numero].dirx > 0)
                        if(niv[bot[numero].diry][bot[numero].dirx-1]>0)
                            (bot[numero].dirx)--;

                    break;
                case DOWN :
                    if(bot[numero].diry < 4)
                        if(niv[bot[numero].diry+1][bot[numero].dirx]>0)
                            (bot[numero].diry)++;

                    break;
                case RIGHT :
                    if(bot[numero].dirx < 4)
                        if(niv[bot[numero].diry][bot[numero].dirx+1]>0)
                            (bot[numero].dirx)++;
                    break;
                default :
                    break;
                }
                break;
            case LIGHT :
                if(niv[bot[numero].diry][bot[numero].dirx] == 2)
                    niv[bot[numero].diry][bot[numero].dirx] = 3;
                else if(niv[bot[numero].diry][bot[numero].dirx] == 3)
                    niv[bot[numero].diry][bot[numero].dirx] = 2;
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
                bot[numero].cptProc=0;
                return 1;
                break;
            }
        }
    }
    bot[0].cptProc++;
    if(cour->suiv==NULL)
        return 0;
    else
        return 1;
}


void showPile(pileAction* pile,BITMAP* tampon, BITMAP * actionforward, BITMAP * actionlight, BITMAP * rotateleft, BITMAP * rotateright, BITMAP * proc)
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
            case PROC :
                draw_sprite(tampon,proc,805+(100*cpt),150+(100*row));
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
