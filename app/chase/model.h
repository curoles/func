#pragma once

//#include <stdlib.h>
//#include <ncurses.h>

#include "func/func.h"

typedef struct Position 
{
    unsigned int x, y;

} Position;

typedef struct GameModel
{
    const unsigned int runner_width;
    const unsigned int runner_height;

    Position runner_pos;
    Position runner_prev_pos;

    void (*update_runner_pos)(struct GameModel* model,
        unsigned int x, unsigned int y);


} GameModel;


EXTERN_INLINE
void GameModel_cleanup(GameModel* model)
{
}

GameModel new_GameModel();
