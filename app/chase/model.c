#define ANCHOR_EXTERN_INLINE
#include "model.h"
#undef ANCHOR_EXTERN_INLINE

static
void GameModel_hunt(GameModel* model)
{
    const Position target = model->runner_prev_pos;//FIXME pos;
    Position pos = model->hunter_pos;

    if (target.x < pos.x)      --pos.x;
    else if (target.x > pos.x) ++pos.x;

    if (target.y < pos.y)      --pos.y;
    else if (target.y > pos.y) ++pos.y;

    model->hunter_prev_pos = model->hunter_pos;
    model->hunter_pos = pos;
}

static
void GameModel_update(
    GameModel* model,
    unsigned int runner_x,
    unsigned int runner_y
)
{
    GameModel_hunt(model); // TODO calculate hunters move when user thinks
    model->runner_prev_pos = model->runner_pos;

    model->runner_pos.x = runner_x;
    model->runner_pos.y = runner_y;

}

static
void GameModel_user_timeout(GameModel* model)
{
    GameModel_hunt(model); 
}

GameModel
new_GameModel(unsigned int width, unsigned int height)
{
    GameModel game_model = {
        .field_width = width,
        .field_height = height,
        .runner_width  = 1,
        .runner_height = 1,
        .runner_pos = {0,0},
        .runner_prev_pos = {0,0},
        .hunter_pos = {width-1, height-1},
        .hunter_prev_pos = {width-1, height-1},
        .update_runner_pos = GameModel_update,
        .user_timeout = GameModel_user_timeout
    };

    return game_model;
}
