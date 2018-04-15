#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

void MapCreation(int **tab, int taillex, int tailley,BITMAP *tampon, BITMAP *sol,BITMAP *tolight, BITMAP *light);
void decoupage(BITMAP *base, BITMAP ***decoupe);

int main()
{
    allegro_init();
    install_mouse();
    int i=0,j=0;
    BITMAP *tampon;
    BITMAP *personnage;
    BITMAP *sol;
    BITMAP *tolight;
    BITMAP *light;
    BITMAP ***decoupe;
    install_keyboard();
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

    ///Creation d'un tableau de BITMAP a 2 dimensions
    decoupe=malloc(4*sizeof(BITMAP**));
    for(i=0; i<9; i++)
        decoupe[i]=malloc(9*sizeof(BITMAP*));
    for(j=0; j<4; j++)
        for(i=0; i<9; i++)
            decoupe[j][i]=create_bitmap(personnage->w/9,personnage->h/8);
    decoupage(personnage,decoupe);
    i=8;
    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        MapCreation(map,5,5,tampon,sol,tolight,light);
        //masked_blit(personnage,tampon,0,0,0,0,personnage->w,personnage->h);
        masked_blit(decoupe[3][i],tampon,0,0,mouse_x,mouse_y,decoupe[3][5]->w,decoupe[3][5]->h);
        i--;
        if(i<0)
            i=8;
        rest(100);
        //circlefill(tampon,mouse_x,mouse_y,20,makecol(255,127,127));
        //masked_blit(personnage,tampon,0,0,mouse_x,mouse_y,60,70);
        blit(tampon,screen,0,0,0,0,1280,720);
    }
    return 0;
}
END_OF_MAIN();

///Recois un tableau et affiche ce dernier
void MapCreation(int **tab, int taillex, int tailley,BITMAP *tampon, BITMAP *sol, BITMAP *tolight,BITMAP *light)
{
    int i=0,j=0; ///Parcourt du tableau de la map
    int x,y; ///Position cartesienne de depart
    int isox,isoy; ///Variable de conversion de cartesion à 2D isometrique

    ///Parcours du tableau
    for(i=0; i<taillex; i++)
    {
        for(j=0; j<tailley; j++)
        {
            x=j*74;
            y=i*74;
            isox=x-y;
            isoy=(x+y)/2;
            if(tab[i][j] == 0) {}
            if(tab[i][j] == 1)
                masked_blit(sol,tampon,0,0,isox+400,isoy+100,sol->w,sol->h);
            if(tab[i][j] == 2)
                masked_blit(tolight,tampon,0,0,isox+400,isoy+100,tolight->w,tolight->h);
            if(tab[i][j] == 3)
                masked_blit(light,tampon,0,0,isox+400,isoy+100,light->w,light->h);
        }
    }
}

///Recois des sprites sur 1 image et decoupe en plein d'images
void decoupage(BITMAP *base, BITMAP ***decoupe)
{
    int i;
    for(i=0; i<9; i++){
        blit(base,decoupe[0][i],(base->w/9)*i,(base->h)/8*0,0,0,decoupe[0][i]->w,decoupe[0][i]->h);
        blit(base,decoupe[1][i],(base->w/9)*i,(base->h)/8*2,0,0,decoupe[1][i]->w,decoupe[1][i]->h);
        blit(base,decoupe[2][i],(base->w/9)*i,(base->h)/8*5,0,0,decoupe[2][i]->w,decoupe[2][i]->h);
        blit(base,decoupe[3][i],(base->w/9)*i,(base->h)/8*7,0,0,decoupe[3][i]->w,decoupe[3][i]->h);
    }
}
