#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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
