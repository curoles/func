/*
 * Install ncurses on Ubuntu:
 * sudo apt-get install libncurses5-dev libncursesw5-dev
 */
#define ANCHOR_EXTERN_INLINE
#include "view.h"
#undef ANCHOR_EXTERN_INLINE

#include <assert.h>

#include "model.h"

static
void GameView_update(GameView* view)
{
    assert(view && view->runner);

    mvderwin(view->runner, view->model->runner_y, view->model->runner_x);

    mvwaddch(view->runner, 0, 0, '*');

    refresh();
}

GameView
new_GameView(struct GameModel* model)
{
    // init curses, determine terminal type
    WINDOW* mainwin = initscr();

    if (mainwin == NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }

    //disable line buffering and set curses to take one character at a time
    cbreak();

    // tell curses not to echo the input back to the screen
    noecho();

    // hide cursor
    curs_set(0);

    // clear the screen
    clear();

    // enable keypad (for arrow keys)
    keypad(mainwin, TRUE);

    GameView game_view = {
        .model   = model,
        .mainwin = mainwin,
        .runner  = subwin(mainwin, model->runner_height, model->runner_width,
                          model->runner_y, model->runner_x),
        .update  = GameView_update
    };

    return game_view;
}
