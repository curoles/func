#pragma once

//#include <stdlib.h>
//#include <ncurses.h>

#include "func/func.h"

typedef struct GameCtrl
{
    void (*run)(struct GameCtrl*);

} GameCtrl;


EXTERN_INLINE
void GameCtrl_cleanup(GameCtrl* ctrl)
{

}

GameCtrl new_GameCtrl();
