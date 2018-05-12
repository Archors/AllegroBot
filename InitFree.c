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

