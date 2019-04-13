#define ANCHOR_EXTERN_INLINE
#include "ctrl.h"
#undef ANCHOR_EXTERN_INLINE

#include <ncurses.h>

#include "view.h"
#include "model.h"

/*static
void display_welcome_message()
{
    printw("Welcome to the game of Chase!\n");
    printw("Press 'q' key to quit at any time.\n");
    printw("Press arrow keys to move.\n");
    printw("Press any key to start the game.\n");
    getch();
    //clear();
}*/

static
void GameCtrl_run(
    struct GameCtrl* ctrl
)
{
    //display_welcome_message();

    GameView* view = ctrl->view;
    GameModel* model = ctrl->model;

    const unsigned int rows = LINES;
    const unsigned int cols = COLS;

    const unsigned int width  = model->runner_width;
    const unsigned int height = model->runner_height;

    unsigned int x = model->runner_x;
    unsigned int y = model->runner_y;

    view->update(view);

    int ch;

    /*  Loop until user hits 'q' to quit  */
    while ( (ch = getch()) != 'q' ) {
	switch ( ch ) {
	case KEY_UP:
	    if ( y > 0 )
		--y;
	    break;
	case KEY_DOWN:
	    if ( y < (rows - height) )
		++y;
	    break;
	case KEY_LEFT:
	    if ( x > 0 )
		--x;
	    break;
	case KEY_RIGHT:
	    if ( x < (cols - width) )
		++x;
	    break;
	case KEY_HOME:
	    x = 0;
	    y = 0;
	    break;
	case KEY_END:
	    x = (cols - width);
	    y = (rows - height);
	    break;
	}

        model->update_runner_pos(model, x, y);
        view->update(view);
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
