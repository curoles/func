/*
 * Install ncurses on Ubuntu:
 * sudo apt-get install libncurses5-dev libncursesw5-dev
 */
#include "view.h"

#include <assert.h>
#include <string.h>

#include "func/foreach.h"
#include "model.h"

enum {FIELD_COLORS=1, RUNNER_COLORS, HUNTER_COLORS, MAZE_COLORS};

/*
 * https://www.linuxjournal.com/content/programming-color-ncurses
 */
static
void GameView_init_colors()
{
    start_color();
    init_pair(FIELD_COLORS, COLOR_BLACK, COLOR_BLACK);
    init_pair(RUNNER_COLORS, COLOR_YELLOW, COLOR_WHITE);
    init_pair(HUNTER_COLORS, COLOR_RED, COLOR_RED);
    init_pair(MAZE_COLORS, COLOR_CYAN, COLOR_GREEN);
    //init_pair(2, COLOR_CYAN, COLOR_BLUE);
    //init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //init_pair(4, COLOR_RED, COLOR_MAGENTA);
}

static
void GameView_update_hunter(GameView* view)
{
    GameModel* model = view->model;

    unsigned int x = model->hunter_prev_pos.x;
    unsigned int y = model->hunter_prev_pos.y;

    attron(COLOR_PAIR(FIELD_COLORS));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(FIELD_COLORS));

    x = model->hunter_pos.x;
    y = model->hunter_pos.y;

    attron(COLOR_PAIR(HUNTER_COLORS));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(HUNTER_COLORS));
}

static
void GameView_update_runner(GameView* view)
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

    // also move cursor where runner is
    move(y, x);
}

static
void GameView_update(GameView* view)
{
    GameView_update_hunter(view);
    GameView_update_runner(view);

    refresh();
}

static
void GameView_show_maze(GameView* view)
{
    attron(COLOR_PAIR(MAZE_COLORS));

    for (unsigned int i = 0; i < view->model->maze_size; ++i) {
        Position pos = view->model->maze[i];
        mvaddch(pos.y, pos.x, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(MAZE_COLORS));

    refresh();
}

static
void GameView_display_welcome()
{
    static char* msg[] = {
    "Welcome to the game of Chase!",
    "Igor Lesik 2019","",
    "Press [ENTER] to start the game","","",
    "Rules and controls:",
    "Move the white cursor to run away from chasing it evil red box.",
    "Use arrow keys of keypad to move the cursor.",
    "Press 'q' key to quit game at any time.",
    };

    int y = LINES/4;
    int x = COLS/2;

    ARRAY_FOREACH(msg, i) {
        mvaddstr(y+i, x - strlen(msg[i])/2, msg[i]);
    }

    getch();
    clear();
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

    if (has_colors()) GameView_init_colors();

    GameView game_view = {
        .model   = model,
        .mainwin = mainwin,
        .update  = GameView_update,
        .show_maze  = GameView_show_maze,
        .display_welcome = GameView_display_welcome
    };

    return game_view;
}
