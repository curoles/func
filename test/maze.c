#define ANCHOR_EXTERN_INLINE
#include "func/maze.h"

bool test1()
{
    Maze maze CLEANUP(Maze_cleanup) = new_Maze(10, 15);

    // maze is empty
    assert(maze.at(&maze, 3, 3) == false);

    maze.set(&maze,  0,  0, true);
    maze.set(&maze,  9, 14, true);
    maze.set(&maze,  5, 12, true);
    maze.set(&maze,  6, 12, true);
    maze.set(&maze,  5, 12, false);

    assert(maze.at(&maze, 0, 0));
    assert(maze.at(&maze, 9, 14));
    assert(maze.at(&maze, 6, 12));
    assert(!maze.at(&maze, 5, 12));

    return true;
}

int main(void)
{
    assert(test1());

    return 0;
}
