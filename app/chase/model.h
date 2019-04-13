#pragma once

//#include <stdlib.h>
//#include <ncurses.h>

#include "func/func.h"

typedef struct GameModel
{
    const unsigned int runner_width;
    const unsigned int runner_height;

    unsigned int runner_x;
    unsigned int runner_y;

    void (*update_runner_pos)(struct GameModel* model,
        unsigned int x, unsigned int y);


} GameModel;


EXTERN_INLINE
void GameModel_cleanup(GameModel* model)
{
}

GameModel new_GameModel();
