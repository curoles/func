#define ANCHOR_EXTERN_INLINE
#include "model.h"
#undef ANCHOR_EXTERN_INLINE


static
void GameModel_update(
    GameModel* model,
    unsigned int runner_x,
    unsigned int runner_y)
{
    model->runner_x = runner_x;
    model->runner_y = runner_y;
}

GameModel
new_GameModel()
{
    GameModel game_model = {
        .runner_width  = 1,
        .runner_height = 1,
        .runner_x = 15,
        .runner_y = 15,
        .update_runner_pos = GameModel_update
    };

    return game_model;
}
