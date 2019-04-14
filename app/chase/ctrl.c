#define ANCHOR_EXTERN_INLINE
#include "ctrl.h"
#undef ANCHOR_EXTERN_INLINE

#include <string.h>
#include <ncurses.h>

#include "view.h"
#include "model.h"

static
void GameCtrl_run(
    struct GameCtrl* ctrl
)
{
    GameView* view = ctrl->view;
    GameModel* model = ctrl->model;

    view->display_welcome();

    const unsigned int rows = model->field_height;
    const unsigned int cols = model->field_width;

    const unsigned int width  = model->runner_width;
    const unsigned int height = model->runner_height;

    unsigned int x = model->runner_pos.x;
    unsigned int y = model->runner_pos.y;

    view->show_maze(view);
    view->update(view);

    // If delay is positive, then read (getch) blocks for delay milliseconds,
    // and returns ERR if there is still no input.
    timeout(2*1000);

    int ch;

    /*  Loop until user hits 'q' to quit  */
    while ( (ch = getch()) != 'q' ) {
	switch ( ch ) {
	case KEY_UP:
	    if (y > 0 && !model->is_maze_pos(model, x, y-1))
		--y;
	    break;
	case KEY_DOWN:
	    if (y < (rows - height) && !model->is_maze_pos(model, x, y+1))
		++y;
	    break;
	case KEY_LEFT:
	    if (x > 0 && !model->is_maze_pos(model, x-1, y))
		--x;
	    break;
	case KEY_RIGHT:
	    if (x < (cols - width) && !model->is_maze_pos(model, x+1, y))
		++x;
	    break;
	//case KEY_HOME:
	//    x = 0;
	//    y = 0;
	//    break;
	//case KEY_END:
	//    x = (cols - width);
	//    y = (rows - height);
	//    break;
	}

        if (x != model->runner_pos.x || y != model->runner_pos.y) {
            model->update_runner_pos(model, x, y);
            view->update(view);
        } else if (ch == ERR) {
            model->user_timeout(model);
            view->update(view);
        }
    }
}

GameCtrl
new_GameCtrl(struct GameView* view, struct GameModel* model)
{
    GameCtrl game_ctrl = {
        .view = view,
        .model = model,
        .run = GameCtrl_run
    };

    return game_ctrl;
}
