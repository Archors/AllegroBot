#include "Prototype.h"
#include "gestionPile.h"

int main()
{
    initalleg();
    int vitesse=5;
    int cliquedrag=0;
    int mem=0;
    int i=0,j=0,k=0;
    int taillex=5, tailley=5;
    int action[5]= {1,2,3,4,5};
    BITMAP *tampon;
    BITMAP *personnage;
    BITMAP *sol;
    BITMAP *tolight;
    BITMAP *light;
    BITMAP *main;
    BITMAP *actionforward;
    BITMAP *actionlight;
    BITMAP *rotateleft;
    BITMAP *rotateright;
    BITMAP *spring;
    BITMAP *souristempo;
    BITMAP *souris;
    int decalx=300, decaly=150;
    t_personnage *bot;
    int **map;
    map=malloc(tailley*sizeof(int*));
    for(i=0; i<tailley; i++)
        map[i]=malloc(taillex*sizeof(int));
    for(i=0; i<tailley; i++)
        for(j=0; j<taillex; j++)
            map[i][j]=1;
    map[4][4]=2;
    map[3][4]=3;
    map[3][3]=0;
    tampon=create_bitmap(1280,720);
    personnage=load_bitmap("Image/Spriterobot.bmp",NULL);
    sol=load_bitmap("Image/Case.bmp",NULL);
    tolight=load_bitmap("Image/Tolight.bmp",NULL);
    light=load_bitmap("Image/Light.bmp",NULL);
    main=load_bitmap("Image/Main.bmp",NULL);
    actionforward=load_bitmap("Image/Forward.bmp",NULL);
    actionlight=load_bitmap("Image/ActionLight.bmp",NULL);
    rotateleft=load_bitmap("Image/RotateLeft.bmp",NULL);
    rotateright=load_bitmap("Image/RotateRight.bmp",NULL);
    spring=load_bitmap("Image/Spring.bmp",NULL);
    souristempo=load_bitmap("Image/Cursor.bmp",NULL);
    souris=create_bitmap(25,31);
    stretch_blit(souristempo,souris,0,0,souristempo->w,souristempo->h,0,0,souris->w,souris->h);
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
    bot[0].x=0;
    bot[0].y=0;
    i=8;
    bot[0].dirx=1;
    bot[0].diry=0;
    bot[0].isox=toisox(bot[0].x,bot[0].y);
    bot[0].isoy=toisoy(bot[0].x,bot[0].y);
    bot[0].dirisox=toisox(bot[0].dirx,bot[0].diry);
    bot[0].dirisoy=toisoy(bot[0].dirx,bot[0].diry);
    pileAction * mainB1 = calloc(1,sizeof(pileAction));
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    addIn(mainB1,0,AVANCER);
    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        MapCreation(map,taillex,tailley,decalx,decaly,tampon,sol,tolight,light);
        if(bot[0].isox != bot[0].dirisox && bot[0].isoy != bot[0].dirisoy)
        {
            deplacement(bot,vitesse);
            draw_sprite(tampon,bot[0].sprite[3][i],bot[0].isox+decalx+35,bot[0].isoy+decaly-10);
            i--;
            if(i<0)
                i=8;
        }
        else
        {
            draw_sprite(tampon,bot[0].sprite[3][8],bot[0].isox+decalx+35,bot[0].isoy+decaly-10);
            i=0;
        }
        draw_sprite(tampon,main,800,100); ///Affichage de la fenetre du main
        draganddrop(tampon,actionforward,actionlight,rotateleft,rotateright,spring,&mem,action,&cliquedrag);
        showPile(mainB1,tampon,actionforward,actionlight,rotateleft,rotateright,spring);
        draw_sprite(tampon,souris,mouse_x,mouse_y); ///Affichage de la souris
        blit(tampon,screen,0,0,0,0,1280,720);
        rest(25);
    }
    liberer(map,bot,taillex);
    return 0;
}
END_OF_MAIN();
