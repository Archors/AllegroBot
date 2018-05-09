#include "Prototype.h"
#include "gestionPile.h"

void liberer(int **map, t_personnage *bot, int taillex)
{
    int i=0, k=0;
    for(k=0; k<5; k++) ///Liberation du bot
    {
        for(i=0; i<4; i++)
            free(bot[k].sprite[i]);
        free(bot[k].sprite);
        ///Free de la liste chainee
        listfree(bot[k].themain);
    }
    free(bot);
    for(i=0; i<taillex; i++) ///Liberation de la map
        free(map[i]);
    free(map);
}

void initalleg()
{
    allegro_init();
    install_mouse();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void initbot(t_personnage* bot)
{
    int i=0;
    bot[0].x=0;
    bot[0].y=0;
    bot[0].dirx=0;
    bot[0].diry=0;
    bot[0].active=1;
    bot[1].x=5;
    bot[1].y=0;
    bot[1].dirx=5;
    bot[1].diry=0;
    bot[1].active=0;
    bot[2].x=0;
    bot[2].y=5;
    bot[2].dirx=0;
    bot[2].diry=5;

    for(i=0;i<5;i++){
    bot[i].actuelsprite=8;
    bot[i].compteur=0;
    bot[i].cpt=0;
    bot[i].cptProc=0;
    bot[i].direction=DOWN;
    bot[i].isox=toisox(bot[i].x,bot[i].y);
    bot[i].isoy=toisoy(bot[i].x,bot[i].y);
    bot[i].dirisox=toisox(bot[i].dirx,bot[i].diry);
    bot[i].dirisoy=toisoy(bot[i].dirx,bot[i].diry);}
}
