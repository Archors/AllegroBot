#include "Prototype.h"

void liberer(int **map, t_personnage *bot)
{
    int i=0, k=0;
    for(k=0; k<5; k++)
    {
            for(i=0; i<4; i++)
                free(bot[k].sprite[i]);
            free(bot[k].sprite);
    }
    free(bot);
    for(i=0;i<9;i++)
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
