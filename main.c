#include "Prototype.h"
#include "gestionPile.h"

int main()
{
    initalleg();
    int vitesse=5;
    int cliquedrag=0;
    int mem=0;
    int lvl=1;
    int boolclique=0;
    int boolmain=0;
    int play=0; ///Booleen de clique sur le bouton de compilation
    int tempobouton=0; ///Temporisation sur le bouton
    int tempodelete=0; ///Temporisation sur l
    int tempoaction=0;
    int i=0,j=0,k=0,l=0;
    int taillex=5, tailley=5;
    int action[5]= {1,2,3,4,5};
    ///Declaration de BITMAP servant a charger les images
    BITMAP *tampon;
    BITMAP *fond;
    BITMAP *personnage;
    BITMAP *personnage2;
    BITMAP *personnage3;
    BITMAP *personnage4;
    BITMAP *personnage5;
    BITMAP *sol;
    BITMAP *tolight;
    BITMAP *light;
    BITMAP *main;
    BITMAP *proc;
    BITMAP *actionforward;
    BITMAP *actionlight;
    BITMAP *rotateleft;
    BITMAP *rotateright;
    BITMAP *actionproc;
    BITMAP *souristempo;
    BITMAP *souris;
    BITMAP *boutonjouer;
    BITMAP *boutonstop;
    BITMAP *boutondelfile;
    BITMAP *menufond;
    BITMAP *menulevel;
    int decalx=300, decaly=150;
    t_personnage *bot;
    int **map;
    map=malloc(tailley*sizeof(int*));
    for(i=0; i<tailley; i++)
        map[i]=malloc(taillex*sizeof(int));
    ///Creation du double buffer
    tampon=create_bitmap(1280,720);
    ///Chargement des images necessaires au jeu
    personnage=load_bitmap("Image/Spriterobot.bmp",NULL);
    personnage2=load_bitmap("Image/Spriterobot2.bmp",NULL);
    personnage3=load_bitmap("Image/Spriterobot3.bmp",NULL);
    personnage4=load_bitmap("Image/Spriterobot4.bmp",NULL);
    personnage5=load_bitmap("Image/Spriterobot5.bmp",NULL);
    sol=load_bitmap("Image/Case.bmp",NULL);
    tolight=load_bitmap("Image/Tolight.bmp",NULL);
    light=load_bitmap("Image/Light.bmp",NULL);
    main=load_bitmap("Image/Main.bmp",NULL);
    proc=load_bitmap("Image/Procedure.bmp",NULL);
    actionforward=load_bitmap("Image/Forward.bmp",NULL);
    actionlight=load_bitmap("Image/ActionLight.bmp",NULL);
    actionproc=load_bitmap("Image/ActionProc.bmp",NULL);
    rotateleft=load_bitmap("Image/RotateLeft.bmp",NULL);
    rotateright=load_bitmap("Image/RotateRight.bmp",NULL);
    souristempo=load_bitmap("Image/Cursor.bmp",NULL);
    fond=load_bitmap("Image/Fond.bmp",NULL);
    boutonjouer=load_bitmap("Image/BoutonJouer.bmp",NULL);
    boutonstop=load_bitmap("Image/BoutonStop.bmp",NULL);
    boutondelfile=load_bitmap("Image/Deletefile.bmp",NULL);
    menufond=load_bitmap("Image/MenuFond.bmp",NULL);
    menulevel=load_bitmap("Image/MenuLevel.bmp",NULL);
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
        bot[k].themain = calloc(1,sizeof(pileAction));
        bot[k].proc = calloc(1,sizeof(pileAction));
    }
    decoupage(personnage,bot[0].sprite);
    decoupage(personnage2,bot[1].sprite);
    decoupage(personnage3,bot[2].sprite);
    decoupage(personnage4,bot[3].sprite);
    decoupage(personnage5,bot[4].sprite);
    /*while (!key[KEY_ESC])
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
            for(i=541; i<740; i++)
                for(j=201; j<270; j++)
                    putpixel(tampon,i,j,makecol(255-getr(getpixel(tampon,i,j)),255-getg(getpixel(tampon,i,j)),255-getb(getpixel(tampon,i,j))));
        }
        draw_sprite(tampon,souris,mouse_x,mouse_y); ///Affichage de la souris
        blit(tampon,screen,0,0,0,0,1280,720);
    }*/
    lvl1(bot,map);
    for(i=0; i<5; i++)
    {
        bot[i].isox=toisox(bot[i].dirx,bot[i].diry);
        bot[i].isoy=toisoy(bot[i].dirx,bot[i].diry);
    }
    toiso(bot);
    while (!key[KEY_ESC])
    {
        blit(fond,tampon,0,0,0,0,fond->w,fond->h); ///Image en fond
        changelvl(bot,&lvl,map,taillex,tailley,&play,&tempoaction); ///Verifie si le niveau est terminee
        MapCreation(map,taillex,tailley,decalx,decaly,tampon,sol,tolight,light);
        bouton(bot,tampon,boutonjouer,boutonstop,boutondelfile,&play,&tempobouton,map,&lvl); ///Gestion des boutons pour jouer et mettre en pause
        for(l=0; l<5; l++)
        {
            if(bot[l].isox != bot[l].dirisox && bot[l].isoy != bot[l].dirisoy)
            {
                deplacement(bot,vitesse,l); ///Modification des coordonnes de deplacement
            }
            else if(play)
            {
                if(tempoaction < 1 && tailleliste(bot[l].themain) > 0)
                {
                    readPile(bot,map,5,5,&tempoaction ); ///Lit la pile d'action
                    bot[0].compteur++;///On incremente le compteur du nombre d'action
                    ///Transforme les coordonnees cartesiennes en coordonnees isometriques
                    toiso(bot);
                }
            }
        }
        tempoaction--;
        affsprite(bot,tampon,decalx,decaly); ///Affichage sprite
        mainproc(&boolmain, tampon,main,proc);
        if(!boolmain)  ///Fenetre du main ouverte
        {
            suppPile(bot[0].themain,&cliquedrag, &tempodelete);
            showPile(bot[0].themain,tampon,actionforward,actionlight,rotateleft,rotateright,actionproc);
            clique(bot[0].themain,action,&boolclique);
        }
        else
        {
            ///Fenetre de la proc ouverte
            suppPile(bot[0].proc,&cliquedrag, &tempodelete);
            showPile(bot[0].proc,tampon,actionforward,actionlight,rotateleft,rotateright,actionproc);
            clique(bot[0].proc,action,&boolclique);
        }
        draganddrop(bot,&boolmain,tampon,actionforward,actionlight,rotateleft,rotateright,actionproc,&mem,action,&cliquedrag);
        draw_sprite(tampon,souris,mouse_x,mouse_y); ///Affichage de la souris
        blit(tampon,screen,0,0,0,0,1280,720);
        rest(20);
    }
    liberer(map,bot,taillex);
    return 0;
}
END_OF_MAIN();
