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
    int i=0,j=0,k=0;
    int taillex=5, tailley=5;
    int action[5]= {1,2,3,4,5};
    ///Declaration de BITMAP servant a charger les images
    BITMAP *tampon;
    BITMAP *fond;
    BITMAP *personnage;
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
    int decalx=300, decaly=150;
    t_personnage *bot;
    int **map;
    map=malloc(tailley*sizeof(int*));
    for(i=0; i<tailley; i++)
        map[i]=malloc(taillex*sizeof(int));
    for(i=0; i<tailley; i++)
        for(j=0; j<taillex; j++)
            map[i][j]=1;
    map[0][0]=2;
    map[3][4]=3;
    map[3][3]=0;
    ///Creation du double buffer
    tampon=create_bitmap(1280,720);
    ///Chargement des images necessaires au jeu
    personnage=load_bitmap("Image/Spriterobot.bmp",NULL);
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
    bot[0].x=0;
    bot[0].y=0;
    bot[0].actuelsprite=8;
    i=8;
    bot[0].dirx=0;
    bot[0].compteur=0;
    bot[0].cpt=0;
    bot[0].diry=0;
    bot[0].direction=DOWN;
    bot[0].isox=toisox(bot[0].x,bot[0].y);
    bot[0].isoy=toisoy(bot[0].x,bot[0].y);
    bot[0].dirisox=toisox(bot[0].dirx,bot[0].diry);
    bot[0].dirisoy=toisoy(bot[0].dirx,bot[0].diry);
    while (!key[KEY_ESC])
    {
        clear_bitmap(tampon);
        blit(fond,tampon,0,0,0,0,fond->w,fond->h); ///Image en fond
        changelvl(bot,&lvl,map,taillex,tailley,&play,&tempoaction); ///Verifie si le niveau est terminee
        MapCreation(map,taillex,tailley,decalx,decaly,tampon,sol,tolight,light);
        bouton(tampon,boutonjouer,boutonstop,&play,&tempobouton); ///Gestion des boutons pour jouer et mettre en pause
        if(bot[0].isox != bot[0].dirisox && bot[0].isoy != bot[0].dirisoy)
            deplacement(bot,vitesse); ///Modification des coordonnes de deplacement
        else if(play == 1)
        {
            if(bot[0].compteur < tailleliste(bot[0].themain) && tempoaction < 1)
            {
                readPile(bot,0,map,5,5,&tempoaction ); ///Lit la pile d'action
                bot[0].compteur++;///On incremente le compteur du nombre d'action
                ///Transforme les coordonnees cartesiennes en coordonnees isometriques
                bot[0].dirisox=toisox(bot[0].dirx,bot[0].diry);
                bot[0].dirisoy=toisoy(bot[0].dirx,bot[0].diry);
            }
        }
        tempoaction--;
        affsprite(bot,tampon,decalx,decaly); ///Affichage sprite
        mainproc(&boolmain, tampon,main,proc);
        if(boolmain == 0)  ///Fenetre du main ouverte
        {
            suppPile(bot[0].themain,&cliquedrag, &tempodelete);
            showPile(bot[0].themain,tampon,actionforward,actionlight,rotateleft,rotateright,actionproc);
            clique(bot[0].themain,action,&boolclique);
        }
        else
        {
            ///Fenetre de la proc ouverte

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
