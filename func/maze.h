#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "func/func.h"
#include "func/xypos.h"

typedef struct Maze
{
    const unsigned int width, height;
    const unsigned int row_size;

    uint8_t* field;

    bool (*at)(struct Maze* maze, unsigned int x, unsigned int y);
    void (*set)(struct Maze* maze, unsigned int x, unsigned int y, bool val);

} Maze;

EXTERN_INLINE
void Maze_cleanup(Maze* maze)
{
    free(maze->field);
}

EXTERN_INLINE
bool Maze_at(Maze* maze, unsigned int x, unsigned int y)
{
    assert(x < maze->width && y < maze->height);
    unsigned int col = x/8;
    uint8_t e = maze->field[y * maze->row_size + col];
    return (e >> (x % 8)) & 0b1;
}

EXTERN_INLINE
void Maze_set(Maze* maze, unsigned int x, unsigned int y, bool val)
{
    assert(x < maze->width && y < maze->height);
    unsigned int col = x/8;
    unsigned int index = y * maze->row_size + col;
    uint8_t mask = 1u << (x % 8);
    if (val) maze->field[index] |= mask;
    else     maze->field[index] &= ~mask;
}

EXTERN_INLINE
Maze new_Maze(unsigned int width, unsigned int height)
{
    Maze maze = {
        .width = width,
        .height = height,
        .row_size = (width + 7)/8,
        .field = calloc(((width+7)/8)*height, sizeof(uint8_t)),
        .at = Maze_at,
        .set = Maze_set
    };

    return maze;
}


typedef struct BFSNode
{
    XYPointUInt p;  // The cordinates of a cell
    int dist;       // cell's distance of from the source
} BFSNode;

#define T BFSNode
#define V VectBFSNode
#define new_V new_VectBFSNode
#define cleanup_V cleanup_VectBFSNode
#include "func/vector.h"

/**
 *
 * @return distance from p1 to p2, -1 if can't find path
 */
EXTERN_INLINE
int Maze_breadth_first_search(Maze* maze, XYPointUInt p1, XYPointUInt p2)
{
    assert(p1.x < maze->width && p2.x < maze->width);
    assert(p1.y < maze->height && p2.y < maze->height);

    //typedef XYPointUInt Point;

    VectBFSNode path CLEANUP(cleanup_VectBFSNode) = new_VectBFSNode(maze->width * maze->height);

    bool visited[maze->height][maze->width]; // struct to keep track of visited cells
    memset(visited, false, sizeof(visited)); // mark all cells as not visited

    // Mark the source cell as visited 
    visited[p1.y][p1.x] = true;

    // Distance of source cell is 0
    //BFSNode node = {p1, 0};
#if 0
    q.push(s);  // Enqueue source cell
  
    // Do a BFS starting from source cell
    while (!path.empty())
    {


    }
#endif
    // Return -1 if destination cannot be reached
    return -1;
}
