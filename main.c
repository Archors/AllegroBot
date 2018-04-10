#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>

int main()
{
    allegro_init();
    install_mouse();
    BITMAP *tampon=create_bitmap(1280,720);
    BITMAP *personnage=load_bitmap("Image/Spriterobot2.bmp",NULL);
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        blit(personnage,tampon,0,0,0,0,personnage->w,personnage->h);
        //circlefill(tampon,mouse_x,mouse_y,20,makecol(255,127,127));
        //masked_blit(personnage,tampon,0,0,mouse_x,mouse_y,60,70);
        blit(tampon,screen,0,0,0,0,1280,720);
    }
    return 0;
}
END_OF_MAIN();
