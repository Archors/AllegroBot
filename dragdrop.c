#include "Prototype.h"
#include "gestionPile.h"

void draganddrop(t_personnage *bot, BITMAP* tampon, BITMAP* forward, BITMAP* light, BITMAP* left, BITMAP* right,BITMAP* spring, int *mem, int action[5], int *cliquedrag)
{
    int j=0;
    for(j=0; j<5; j++)
    {
        switch(action[j])
        {
        case AVANCER:
            draw_sprite(tampon,forward,100+j*100,600);
            break;
        case LIGHT:
            draw_sprite(tampon,light,100+j*100,600);
            break;
        case ROTATE_LEFT    :
            draw_sprite(tampon,left,100+j*100,600);
            break;
        case ROTATE_RIGHT:
            draw_sprite(tampon,right,100+j*100,600);
            break;
        case JUMP:
            draw_sprite(tampon,spring,100+j*100,600);
            break;
        }
        if(mouse_b&1 && (mouse_x>100+j*100 && mouse_x < 100+(j+1)*100) && mouse_y > 600 && mouse_y < 700 && (*cliquedrag) != 1)
        {
            if(action[j] != 0)
            {
                (*cliquedrag)=1;
                (*mem)=action[j];
            }
        }

    }
    if((*cliquedrag) == 1)
    {
        switch(*mem)
        {
        case AVANCER:
            draw_sprite(tampon,forward,mouse_x-50,mouse_y-50);
            break;
        case LIGHT:
            draw_sprite(tampon,light,mouse_x-50,mouse_y-50);
            break;
        case ROTATE_LEFT:
            draw_sprite(tampon,left,mouse_x-50,mouse_y-50);
        case ROTATE_RIGHT:
            draw_sprite(tampon,right,mouse_x-50,mouse_y-50);
            break;
        case JUMP:
            draw_sprite(tampon,spring,mouse_x-50,mouse_y-50);
            break;
        }
        drag(bot[0].themain,cliquedrag,mem);
    }
    if(!mouse_b&1)
    {
        (*cliquedrag)=0;
        (*mem)=0;
    }
}

void drag(pileAction* pile, int *cliquedrag,int *mem)
{
    int cpt=0;
    int row=0;
    int nb=0;
    t_action * cour=pile->first;
    if(cour!=NULL)
    {
        while(cour!=NULL)
        {
            if(*cliquedrag == 1 && !mouse_b&1 && mouse_x > 805+(100*cpt) && mouse_x < 905+(100*cpt) && mouse_y > 150+(100*row) && mouse_y < 250+(100*row))
            {
                addIn(pile,cpt+(row*4),*mem);
                *cliquedrag=0;
                *mem=0;
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

void clique(pileAction *pile, int action[5],int *clique)
{
    int j=0;
    for(j=0; j<5; j++)
    {
        if(mouse_b&1 && (mouse_x>100+j*100 && mouse_x < 100+(j+1)*100) && mouse_y > 600 && mouse_y < 700)
            *clique=1;
        if(!mouse_b&1 && (mouse_x>100+j*100 && mouse_x < 100+(j+1)*100) && mouse_y > 600 && mouse_y < 700 && (*clique)==1)
        {
            addToEnd(pile,action[j]);
        }
    }
    if(!mouse_b&1)
        *clique = 0;
}
