/*
 * Install ncurses on Ubuntu:
 * sudo apt-get install libncurses5-dev libncursesw5-dev
 */
#define ANCHOR_EXTERN_INLINE
#include "view.h"
#undef ANCHOR_EXTERN_INLINE

#include <assert.h>

#include "model.h"

enum {FIELD_COLORS=1, RUNNER_COLORS};

/*
 * https://www.linuxjournal.com/content/programming-color-ncurses
 */
static
void GameView_init_colors()
{
    start_color();
    init_pair(FIELD_COLORS, COLOR_BLACK, COLOR_BLACK);
    init_pair(RUNNER_COLORS, COLOR_YELLOW, COLOR_WHITE);
    //init_pair(2, COLOR_CYAN, COLOR_BLUE);
    //init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //init_pair(4, COLOR_RED, COLOR_MAGENTA);
}

static
void GameView_update(GameView* view)
{
    GameModel* model = view->model;

    unsigned int x = model->runner_prev_pos.x;
    unsigned int y = model->runner_prev_pos.y;

    attron(COLOR_PAIR(FIELD_COLORS));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(FIELD_COLORS));

    x = model->runner_pos.x;
    y = model->runner_pos.y;

    attron(COLOR_PAIR(RUNNER_COLORS));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(RUNNER_COLORS));

    // also move cursor
    move(y, x);

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

    // show cursor
    curs_set(2);

    // clear the screen
    clear();

    // enable keypad (for arrow keys)
    keypad(mainwin, TRUE);

    if (has_colors()) GameView_init_colors();

    GameView game_view = {
        .model   = model,
        .mainwin = mainwin,
        .update  = GameView_update
    };

    return game_view;
}
