#include "Prototype.h"

void draganddrop(pileAction *mainB1, BITMAP* tampon, BITMAP* forward, BITMAP* light, BITMAP* left, BITMAP* right,BITMAP* spring, int *mem, int action[5], int *cliquedrag)
{
    int j=0;
    for(j=0; j<5; j++)
    {
        switch(action[j])
        {
        case 1:
            draw_sprite(tampon,forward,100+j*100,600);
            break;
        case 2:
            draw_sprite(tampon,light,100+j*100,600);
            break;
        case 3:
            draw_sprite(tampon,left,100+j*100,600);
            break;
        case 4:
            draw_sprite(tampon,right,100+j*100,600);
            break;
        case 5:
            draw_sprite(tampon,spring,100+j*100,600);
            break;
        }
        if(mouse_b&1 && (mouse_x>100+j*100 && mouse_x < 100+(j+1)*100) && mouse_y > 600 && mouse_y < 700 && (*cliquedrag) != 1)
        {
            ///Envoi de l'instruction dans la pile
                    addIn(mainB1,0,action[j]);

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
        case 1:
            draw_sprite(tampon,forward,mouse_x-50,mouse_y-50);
            break;
        case 2:
            draw_sprite(tampon,light,mouse_x-50,mouse_y-50);
            break;
        case 3:
            draw_sprite(tampon,left,mouse_x-50,mouse_y-50);
        case 4:
            draw_sprite(tampon,right,mouse_x-50,mouse_y-50);
            break;
        case 5:
            draw_sprite(tampon,spring,mouse_x-50,mouse_y-50);
            break;
        }
    }
    if(!mouse_b&1)
    {
//        if(mouse_x < )
        (*cliquedrag)=0;
        (*mem)=0;
    }
}
