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
#define Q QueueBFSNode
#define new_Q new_QueueBFSNode
#define cleanup_Q cleanup_QueueBFSNode
#include "func/queue.h"

/**
 *
 * @return distance from p1 to p2, -1 if can't find path
 */
EXTERN_INLINE
int Maze_breadth_first_search(Maze* maze, XYPointUInt p1, XYPointUInt p2)
{
    assert(p1.x < maze->width && p2.x < maze->width);
    assert(p1.y < maze->height && p2.y < maze->height);

    bool is_valid(XYPointInt p) {
        return (p.x >=0 && p.x < maze->width) &&
               (p.y >=0 && p.y < maze->height) && !maze->at(maze, p.x, p.y);
    }

    QueueBFSNode path CLEANUP(cleanup_QueueBFSNode) = new_QueueBFSNode(maze->width * maze->height);

    bool visited[maze->height][maze->width]; // struct to keep track of visited cells
    memset(visited, false, sizeof(visited)); // mark all cells as not visited

    // Mark the source cell as visited 
    visited[p1.y][p1.x] = true;

    // Distance of source cell is 0
    BFSNode node = {p1, 0};

    path.push_back(&path, node);  // Enqueue source cell

    static XYPointInt neighbours[4] = {{1,0},{-1,0},{0,1},{0,-1}};

    // Do a BFS starting from source cell
    while (path.size > 0)
    {
        node = *(path.front(&path));

        // If we have reached the destination cell, we are done.
        if (node.p.x == p2.x && node.p.y == p2.y)
            return node.dist;

        // Otherwise dequeue the front cell in the queue
        // and enqueue its adjacent cells.
        path.pop_front(&path);

        for (unsigned int i = 0; i < 4; ++i) {
            XYPointInt p = {node.p.x + neighbours[i].x, node.p.y + neighbours[i].y};

            // if adjacent cell is valid and not visited yet, enqueue it
            if (is_valid(p) && !visited[p.y][p.x]) {
                // mark cell as visited and enqueue it
                visited[p.y][p.x] = true;
                BFSNode adjnode = {.p = {p.x,p.y}, .dist = node.dist + 1};
                path.push_back(&path, adjnode);
            }
        }
    }

    // Return -1 if destination cannot be reached
    return -1;
}
