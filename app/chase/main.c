#include <stdlib.h>
#include <ncurses.h>

#include "func/func.h"

#include "view.h"
#include "model.h"
#include "ctrl.h"

int main(void)
{
    if (initscr() == NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }

    if (COLS < 30 || LINES < 20) {
        fprintf(stderr, "Terminal window %dx%d is too small, make it bigger.\n", COLS, LINES);
        endwin();
	exit(EXIT_FAILURE);
    }

    GameModel model CLEANUP(GameModel_cleanup) = new_GameModel(COLS, LINES);

    GameView view CLEANUP(GameView_cleanup) = new_GameView(&model);

    GameCtrl ctrl CLEANUP(GameCtrl_cleanup) = new_GameCtrl(&view, &model);

    ctrl.run(&ctrl);

    return EXIT_SUCCESS;
}
