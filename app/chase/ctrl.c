#define ANCHOR_EXTERN_INLINE
#include "ctrl.h"
#undef ANCHOR_EXTERN_INLINE

#include <string.h>
#include <ncurses.h>

#include "view.h"
#include "model.h"

static
void display_welcome_message()
{
    static char* msg[] = {
    "Welcome to the game of Chase!",
    "Igor Lesik 2019",
    "Press arrow keys to move cursor.",
    "Press 'q' key to quit game at any time.",
    "OK"
    };

    int y = LINES/3;
    int x = COLS/2;

    mvaddstr(y,   x - strlen(msg[0])/2, msg[0]);
    mvaddstr(y+1, x - strlen(msg[1])/2, msg[1]);

    mvaddstr(y+3, x - strlen(msg[2])/2, msg[2]);
    mvaddstr(y+4, x - strlen(msg[3])/2, msg[3]);

    mvaddstr(y+6, x - strlen(msg[4])/2, msg[4]);

    getch();
    clear();
}

static
void GameCtrl_run(
    struct GameCtrl* ctrl
)
{
    display_welcome_message();

    GameView* view = ctrl->view;
    GameModel* model = ctrl->model;

    const unsigned int rows = LINES;
    const unsigned int cols = COLS;

    const unsigned int width  = model->runner_width;
    const unsigned int height = model->runner_height;

    unsigned int x = model->runner_pos.x;
    unsigned int y = model->runner_pos.y;

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
