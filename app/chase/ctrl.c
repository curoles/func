#define ANCHOR_EXTERN_INLINE
#include "ctrl.h"
#undef ANCHOR_EXTERN_INLINE

#include <ncurses.h>

void GameCtrl_run(struct GameCtrl* ctrl)
{
printw("Hello World !!!");
char buf[1024];
sprintf(buf,"lines %d cols %d\n", LINES, COLS);
printw(buf);
getch();

}

GameCtrl
new_GameCtrl()
{
    GameCtrl game_ctrl;

    game_ctrl.run = GameCtrl_run;

    return game_ctrl;
}
