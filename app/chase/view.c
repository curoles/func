#define ANCHOR_EXTERN_INLINE
#include "view.h"
#undef ANCHOR_EXTERN_INLINE

GameView
new_GameView(struct GameModel* model)
{
    initscr(); // init curses, determine terminal type

    GameView game_view = {
        .model = model
    };

    return game_view;
}
