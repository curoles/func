#include <stdio.h>

#define ANCHOR_EXTERN_INLINE
#include "func/maze.h"

bool test1(void)
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

bool test2(void)
{
    Maze maze CLEANUP(Maze_cleanup) = new_Maze(5, 5);
    maze.set(&maze,  1,  1, true); // 0 0 0 0 0
    maze.set(&maze,  2,  1, true); // 0 1 1 1 0
    maze.set(&maze,  3,  1, true); // 0 0 1 0 0
    maze.set(&maze,  2,  2, true); // 0 0 0 1 0
    maze.set(&maze,  3,  3, true); // 0 0 0 0 0

    QueueBFSNode path CLEANUP(cleanup_QueueBFSNode) =
        new_QueueBFSNode(maze.width * maze.height);

    XYPointUInt p1 = {0, 0};
    XYPointUInt p2 = {3, 2};

    int dist = Maze_breadth_first_search(&maze, p1, p2, &path);
    assert(dist == 7); // {1,0} {2,0} {3,0} {4,0} {4,1} {4,2} {3,2}

    p1.x = 0; p1.y = 4;
    path.reset(&path);
    dist = Maze_breadth_first_search(&maze, p1, p2, &path);
    assert(dist == 7);
    printf("dist=%d path_size=%u\n", dist, path.size);

    path.foreach(&path, lambda(void, (unsigned i, BFSNode* node) {
         printf("frontier[%u] node.dist=%u x=%u y=%u o.x=%u o.y=%u\n",
             i, node->dist, node->p.x, node->p.y, node->o.x, node->o.y);
         //assert(*e == (i + 1));
    }));

    XYPointUInt p;

    for (int i = 0; i < (dist - 2); ++i) {
        p = path.front(&path)->o;
        printf(" {%u,%u}\n", p.x, p.y);
        path.reset(&path);
        Maze_breadth_first_search(&maze, p1, p, &path);
    }

    return true;
}

bool test3(void)
{
    Maze maze CLEANUP(Maze_cleanup) = new_Maze(5, 5);
    maze.set(&maze,  1,  1, true); // 0 0 0 0 0
    maze.set(&maze,  2,  1, true); // 0 1 1 1 0
    maze.set(&maze,  3,  1, true); // 0 0 1 0 0
    maze.set(&maze,  2,  2, true); // 0 0 0 1 0
    maze.set(&maze,  3,  3, true); // 0 0 0 0 0

    QueueBFSNode path CLEANUP(cleanup_QueueBFSNode) =
        new_QueueBFSNode(maze.width * maze.height);

    QueueBFSNode crawler CLEANUP(cleanup_QueueBFSNode) =
        new_QueueBFSNode(maze.width * maze.height);

    XYPointUInt p1 = {0, 0};
    XYPointUInt p2 = {3, 2};

    int dist = Maze_breadth_first_path(&maze, p1, p2, &crawler, &path);
    assert(dist == 7); // {1,0} {2,0} {3,0} {4,0} {4,1} {4,2} {3,2}

    path.foreach(&path, lambda(void, (unsigned i, BFSNode* node) {
         printf("path[%u] node.dist=%u x=%u y=%u o.x=%u o.y=%u\n",
             i, node->dist, node->p.x, node->p.y, node->o.x, node->o.y);
         //assert(*e == (i + 1));
    }));

    return true;
}

int main(void)
{
    assert(test1());
    assert(test2());
    assert(test3());

    return 0;
}
