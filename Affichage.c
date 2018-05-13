#include "Prototype.h"
#include "gestionPile.h"

///Recois un tableau et affiche ce dernier
void MapCreation(int **tab, int taillex, int tailley,int decalx, int decaly,BITMAP *tampon, BITMAP *sol, BITMAP *tolight,BITMAP *light)
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
            switch (tab[i][j])
            {
            case 1 :
                masked_blit(sol,tampon,0,0,isox+decalx,isoy+decaly,sol->w,sol->h);
                break;
            case 2 :
                masked_blit(tolight,tampon,0,0,isox+decalx,isoy+decaly,tolight->w,tolight->h);
                break;
            case 3 :
                masked_blit(light,tampon,0,0,isox+decalx,isoy+decaly,light->w,light->h);
                break;
            }
        }
    }
}


///Reception des sprites sur 1 image et decoupe en plusieurs images
void decoupage(BITMAP *base, BITMAP ***decoupe)
{
    int i;
    for(i=0; i<9; i++)
    {
        blit(base,decoupe[0][i],(base->w/9)*i,(base->h)/8*0,0,0,decoupe[0][i]->w,decoupe[0][i]->h);
        blit(base,decoupe[1][i],(base->w/9)*i,(base->h)/8*2,0,0,decoupe[1][i]->w,decoupe[1][i]->h);
        blit(base,decoupe[2][i],(base->w/9)*i,(base->h)/8*5,0,0,decoupe[2][i]->w,decoupe[2][i]->h);
        blit(base,decoupe[3][i],(base->w/9)*i,(base->h)/8*7,0,0,decoupe[3][i]->w,decoupe[3][i]->h);
    }
}

int toisox(int x, int y)
{
    return(x*74-y*74);
}

int toisoy(int x, int y)
{
    return((x*74+y*74)/2);
}

void deplacement(t_personnage *bot, int vitesse, int numero)
{
    int i=numero;

    bot[i].isox += (bot[i].dirisox - bot[i].isox) * vitesse / (sqrt((bot[i].isox - bot[i].dirisox)*(bot[i].isox - bot[i].dirisox) + (bot[i].isoy - bot[i].dirisoy)*(bot[i].isoy - bot[i].dirisoy)));
    bot[i].isoy += (bot[i].dirisoy - bot[i].isoy) * vitesse / (sqrt((bot[i].isox - bot[i].dirisox)*(bot[i].isox - bot[i].dirisox) + (bot[i].isoy - bot[i].dirisoy)*(bot[i].isoy - bot[i].dirisoy)));
    if(bot[i].isox < 15+bot[i].dirisox && bot[i].isoy < 15+bot[i].dirisoy  && bot[i].isox > bot[i].dirisox-15 && bot[i].isoy > bot[i].dirisoy-15)
    {
        bot[i].isox=bot[i].dirisox;
        bot[i].isoy=bot[i].dirisoy;
    }
}

void bouton(t_personnage* bot, BITMAP* tampon, BITMAP* jouer, BITMAP* stop,BITMAP* delpile, int *play, int *tempo,int **map,int *lvl)
{
    int i=0;
    if(tempo > 0)
        (*tempo)--;
    if(*play == 0)
        draw_sprite(tampon,jouer,800,20); ///Affichage du bouton pour lancer la compilation
    if(*play == 1)
        draw_sprite(tampon,stop,800,20);
    if(mouse_b&1 && mouse_x > 800 && mouse_y > 20 && mouse_x < 800 + jouer->w && mouse_y < 20 + jouer->h && *tempo < 0)
    {
        if(*play==0)
        {
            *play=1;
            *tempo = 13;
        }
        else
        {
            *play=0;
            *tempo=13;
        }
    }
    draw_sprite(tampon,delpile,920,20);
    if(mouse_b&1 && mouse_x > 920 && mouse_y > 20 && mouse_x < 920 + delpile->w && mouse_y < 20 + delpile->h)
        for(i=0; i<5; i++)
        {
            listfree(bot[i].themain);
            listfree(bot[i].proc);
            resetbot(bot);
            switch(*lvl)
            {
            case 1:
                lvl1(bot,map);
                break;
            case 2:
                lvl2(bot,map);
                break;
            case 3:
                lvl3(bot,map);
                break;
            }
            *play=0;
        }
}

void affsprite(t_personnage* bot,BITMAP* tampon,int decalx, int decaly)
{
    int i=0;
    for(i=0; i<5; i++)
    {
        switch (bot[i].direction)
        {
        case UP:
            draw_sprite(tampon, bot[i].sprite[UP][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[i].isoy+decaly-10);
            break;
        case DOWN:
            draw_sprite(tampon, bot[i].sprite[DOWN][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[i].isoy+decaly-10);
            break;
        case LEFT:
            draw_sprite(tampon, bot[i].sprite[LEFT][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[i].isoy+decaly-10);
            break;
        case RIGHT:
            draw_sprite(tampon, bot[i].sprite[RIGHT][bot[i].actuelsprite], bot[i].isox+decalx+35,bot[i].isoy+decaly-10);
            break;
        }
        if(bot[i].isox == bot[i].dirisox && bot[i].isoy == bot[i].dirisoy)
            bot[i].actuelsprite=8;
        else
        {
            bot[i].actuelsprite--;
            if(bot[i].actuelsprite < 0)
                bot[i].actuelsprite = 8;
        }

    }
}

void mainproc(int *booleen,BITMAP* tampon, BITMAP *main, BITMAP *proc)
{
    if(mouse_b&1 && mouse_x > 800 && mouse_y > 100 && mouse_x < 872 && mouse_y < 142)
        *booleen=0;
    if(mouse_b&1 && mouse_x > 872 && mouse_y > 100 && mouse_x < 949 && mouse_y < 142)
        *booleen=1;
    if(*booleen == 1)
    {
        draw_sprite(tampon,main,800,100); ///Affichage de la fenetre du main
        draw_sprite(tampon,proc,800,100); ///Affichage de la fenetre de la proc
    }
    else
    {
        draw_sprite(tampon,proc,800,100); ///Affichage de la fenetre de la proc
        draw_sprite(tampon,main,800,100); ///Affichage de la fenetre du main
    }
}

void toiso(t_personnage* bot)
{
    int i=0;
    for(i=0; i<5; i++)
    {
        bot[i].dirisox=toisox(bot[i].dirx,bot[i].diry);
        bot[i].dirisoy=toisoy(bot[i].dirx,bot[i].diry);
    }
}

void menulvl(BITMAP* tampon, BITMAP* menufond, BITMAP* menulevel, BITMAP* souris, int *lvl, int *choix,t_personnage* bot, int** map)
{
    int i=0,j=0;
    while (*choix != 1 && !key[KEY_ESC])
    {
        draw_sprite(tampon,menufond,0,0);
        draw_sprite(tampon,menulevel,0,0);
        rect(tampon,540,200,740,270,makecol(255,0,0));
        rect(tampon,540,300,740,370,makecol(255,0,0));
        rect(tampon,540,405,740,475,makecol(255,0,0));
        rect(tampon,540,510,740,580,makecol(255,0,0));
        rect(tampon,540,610,740,680,makecol(255,0,0));
        if ( mouse_x>=540 && mouse_y>=200 && mouse_x<=740 && mouse_y <=270)
        {
            if(mouse_b&1){
            *lvl=1;
            *choix=1;}
            for(i=541; i<740; i++)
                for(j=201; j<270; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        if ( mouse_x>=540 && mouse_y>=300 && mouse_x<=740 && mouse_y <=370)
        {
            if(mouse_b&1){
            *lvl=2;
            *choix=1;}
            for(i=541; i<740; i++)
                for(j=301; j<370; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        if ( mouse_x>=540 && mouse_y>=405 && mouse_x<=740 && mouse_y <=475)
        {

            if(mouse_b&1){
            *lvl=3;
            *choix=1;}
            for(i=541; i<740; i++)
                for(j=406; j<475; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        if ( mouse_x>=540 && mouse_y>=510 && mouse_x<=740 && mouse_y <=580)
        {
            if(mouse_b&1){
            *lvl=4;
            *choix=1;}
            for(i=541; i<740; i++)
                for(j=511; j<580; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        if ( mouse_x>=540 && mouse_y>=610 && mouse_x<=740 && mouse_y <=680)
        {
            if(mouse_b&1){
            *lvl=5;
            *choix=1;}
            for(i=541; i<740; i++)
                for(j=611; j<680; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        draw_sprite(tampon,souris,mouse_x,mouse_y); ///Affichage de la souris
        blit(tampon,screen,0,0,0,0,1280,720);
        switch (*lvl)
    {
    case 1:
        resetbot(bot);
        listfree(bot[0].themain);
        listfree(bot[0].proc);
        lvl1(bot,map);
        break;
    case 2:
        resetbot(bot);
        listfree(bot[0].themain);
        listfree(bot[0].proc);
        lvl2(bot,map);
        break;
    case 3:
        resetbot(bot);
        listfree(bot[0].themain);
        listfree(bot[0].proc);
        lvl3(bot,map);
        break;
    case 4:
        resetbot(bot);
        listfree(bot[0].themain);
        listfree(bot[0].proc);
        lvl4(bot,map);
        break;
    case 5:
        resetbot(bot);
        listfree(bot[0].themain);
        listfree(bot[0].proc);
        //lvl5(bot,map);
        break;
    }
    }
}
