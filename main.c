#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>

int main()
{
    allegro_init();
    install_mouse();
    BITMAP *tampon=create_bitmap(800,600);
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        circlefill(tampon,mouse_x,mouse_y,20,makecol(255,127,127));
        blit(tampon,screen,0,0,0,0,800,600);
    }

    return 0;
}
END_OF_MAIN();
