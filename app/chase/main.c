#include <stdlib.h>
#include <ncurses.h>

#include "func/func.h"

#include "view.h"
#include "model.h"
#include "ctrl.h"

int main(void)
{
    GameModel model CLEANUP(GameModel_cleanup) = new_GameModel();

    GameView view CLEANUP(GameView_cleanup) = new_GameView(&model);

    GameCtrl ctrl CLEANUP(GameCtrl_cleanup) = new_GameCtrl();

    ctrl.run(&ctrl);

    return EXIT_SUCCESS;
}
