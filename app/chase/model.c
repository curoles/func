#include "model.h"

#include <time.h>

static
bool GameModel_is_maze_pos(GameModel* model, unsigned int x, unsigned int y)
{
    Maze* maze = &model->maze;

    return maze->at(maze, x, y);
}

static
void GameModel_hunt(GameModel* model)
{
    const Position target = model->runner_pos;
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
    GameModel_hunt(model); // TODO calculate hunter's move when user thinks
    model->runner_prev_pos = model->runner_pos;

    model->runner_pos.x = runner_x;
    model->runner_pos.y = runner_y;

}

static
void GameModel_user_timeout(GameModel* model)
{
    GameModel_hunt(model); 
}

static
void make_maze(Maze* maze, unsigned int size, unsigned int width, unsigned int height)
{
    /* initialize random seed: */
    srand(time(NULL));

    unsigned int rand_0_8() { return rand() % 9; }
    unsigned int rand_width() { return (rand() % (width-2)) + 1; }
    unsigned int rand_height() { return (rand() % (height-2)) + 1; }

    unsigned int x = rand_width();
    unsigned int y = rand_height();

    for (unsigned int i = 0; i < size; )
    {
        unsigned int dir = rand_0_8();
        if (dir == 0) { // jump and build maze in some other location
            x = rand_width();
            y = rand_height();
            continue;
        }
        switch (dir) {
        case 1 ... 2: x = (x < (width-3))? x+1:x-1; break;
        case 3 ... 4: x = (x > 3)? x-1:x+1; break;
        case 5 ... 6: y = (y < (height-3))? y+1:y-1; break;
        case 7 ... 8: y = (y > 3)? y-1:y+1; break;
        }

        if (maze->at(maze, x, y)) continue;

        maze->set(maze, x, y, true);

        ++i;
    }
}

GameModel
new_GameModel(unsigned int width, unsigned int height)
{
    unsigned int maze_size = (width * height)/4;

    GameModel game_model = {
        .field_width = width,
        .field_height = height,
        .runner_width  = 1,
        .runner_height = 1,
        .runner_pos = {0,0},
        .runner_prev_pos = {0,0},
        .hunter_pos = {width-1, height-1},
        .hunter_prev_pos = {width-1, height-1},
        .maze_size = maze_size,
        .maze = new_Maze(width, height),
        .update_runner_pos = GameModel_update,
        .user_timeout = GameModel_user_timeout,
        .is_maze_pos = GameModel_is_maze_pos
    };

    make_maze(&game_model.maze, maze_size, width, height);

    return game_model;
}
