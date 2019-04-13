#pragma once

#include <stdlib.h>
#include <ncurses.h>

#include "func/func.h"

typedef struct GameView
{
    struct GameModel* model;

    WINDOW* mainwin;


    void (*update)(struct GameView*);
    void (*display_welcome)();

} GameView;


EXTERN_INLINE
void GameView_cleanup(GameView* view)
{
    delwin(view->mainwin);

    // exit the curses environment and return the terminal screen to normal control
    endwin();
}

GameView new_GameView(struct GameModel* model);
