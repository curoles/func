#define ANCHOR_EXTERN_INLINE
#include "model.h"
#undef ANCHOR_EXTERN_INLINE


static
void GameModel_update(
    GameModel* model,
    unsigned int runner_x,
    unsigned int runner_y)
{
    model->runner_prev_pos = model->runner_pos;

    model->runner_pos.x = runner_x;
    model->runner_pos.y = runner_y;
}

GameModel
new_GameModel()
{
    GameModel game_model = {
        .runner_width  = 1,
        .runner_height = 1,
        .runner_pos = {10,10},
        .runner_prev_pos = {10,10},
        .update_runner_pos = GameModel_update
    };

    return game_model;
}
