#include "Prototype.h"

int main()
{
    allegro_init();
    install_mouse();
    install_keyboard();
    int i=0,j=0,k=0;
    BITMAP *tampon;
    BITMAP *personnage;
    BITMAP *sol;
    BITMAP *tolight;
    BITMAP *light;
    t_personnage *bot;
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int **map;
    map=malloc(10*sizeof(int*));
    for(i=0; i<10; i++)
        map[i]=malloc(10*sizeof(int));
    for(i=0; i<10; i++)
        for(j=0; j<10; j++)
            map[i][j]=1;

    map[4][4]=2;
    map[3][4]=3;
    map[3][3]=0;
    tampon=create_bitmap(1280,720);
    personnage=load_bitmap("Image/Spriterobot.bmp",NULL);
    sol=load_bitmap("Image/Case.bmp",NULL);
    tolight=load_bitmap("Image/Tolight.bmp",NULL);
    light=load_bitmap("Image/Light.bmp",NULL);

    bot = calloc(5,sizeof(t_personnage)); ///5 bots
    for(k=0; k<5; k++) ///On parcourt les 5 bots
    {
        bot[k].sprite=malloc(4*sizeof(BITMAP**)); ///4 possibilites de deplacement
        for(i=0; i<4; i++)
            bot[k].sprite[i]=malloc(9*sizeof(BITMAP*)); ///9 sprite par deplacement
        for(j=0; j<4; j++)
            for(i=0; i<9; i++)
                bot[k].sprite[j][i]=create_bitmap(personnage->w/9,personnage->h/8);

    }
    decoupage(personnage,bot[0].sprite);
    i=8;
    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        MapCreation(map,5,5,tampon,sol,tolight,light);
        //masked_blit(personnage,tampon,0,0,0,0,personnage->w,personnage->h);
        masked_blit(bot[0].sprite[3][i],tampon,0,0,mouse_x,mouse_y,bot[0].sprite[3][5]->w,bot[0].sprite[3][5]->h);
        i--;
        if(i<0)
            i=8;
        rest(100);
        //circlefill(tampon,mouse_x,mouse_y,20,makecol(255,127,127));
        //masked_blit(personnage,tampon,0,0,mouse_x,mouse_y,60,70);
        blit(tampon,screen,0,0,0,0,1280,720);
    }
    liberer(map,bot);
    return 0;
}
END_OF_MAIN();
