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
