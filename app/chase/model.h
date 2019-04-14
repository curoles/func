#pragma once

#include <stdlib.h>

#include "func/func.h"

typedef struct Position 
{
    unsigned int x, y;

} Position;

typedef struct GameModel
{
    const unsigned int field_width;
    const unsigned int field_height;

    const unsigned int runner_width;
    const unsigned int runner_height;

    Position runner_pos;
    Position runner_prev_pos;

    Position hunter_pos;
    Position hunter_prev_pos;

    const unsigned int maze_size;
    Position* maze;

    void (*update_runner_pos)(struct GameModel* model,
        unsigned int x, unsigned int y);

    void (*user_timeout)(struct GameModel* model);

    bool (*is_maze_pos)(struct GameModel* model,
        unsigned int x, unsigned int y);

} GameModel;


EXTERN_INLINE
void GameModel_cleanup(GameModel* model)
{
    free(model->maze);
}

GameModel new_GameModel(unsigned int width, unsigned int height);
