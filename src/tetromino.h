//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#ifndef LOWRIS_TETROMINO_H
#define LOWRIS_TETROMINO_H

#include <stdbool.h>
#include "board.h"

#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 4

#define TETR(x, y) ((x) + (y) * TETROMINO_WIDTH)

typedef enum {
    I, O, T, J, L, S, Z
} lowris_tetrominoes;

typedef struct {
    int32_t x, last_x;
    int32_t y, last_y;

    int32_t rotation, last_rot;
    lowris_tetrominoes tetromino;
} lowris_current_tetromino;

typedef struct {
    int32_t x;
    int32_t y;
} lowris_kicktable_entry;

static const lowris_kicktable_entry srs_ljstz_table[40] = {
        /* TEST 1  */       /* TEST 2  */       /* TEST 3 */        /* TEST 4  */       /* TEST 5  */
/*0->R*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y =  1}, {.x =  0, .y = -2}, {.x = -1, .y = -2},
/*R->0*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y = -1}, {.x =  0, .y =  2}, {.x =  1, .y =  2},
/*R->2*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y = -1}, {.x =  0, .y =  2}, {.x =  1, .y =  2},
/*2->R*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y =  1}, {.x =  0, .y = -2}, {.x = -1, .y = -2},
/*2->L*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y =  1}, {.x =  0, .y = -2}, {.x =  1, .y = -2},
/*L->2*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y = -1}, {.x =  0, .y =  2}, {.x = -1, .y =  2},
/*L->0*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y = -1}, {.x =  0, .y =  2}, {.x = -1, .y =  2},
/*0->L*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y =  1}, {.x =  0, .y = -2}, {.x =  1, .y = -2}
};

static const lowris_kicktable_entry srs_i_table[40] = {
        {.x =  0, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y = -1}, {.x =  1, .y =  2},
        {.x =  0, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  1}, {.x = -1, .y = -2},
        {.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  2}, {.x =  2, .y = -1},
        {.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y = -2}, {.x = -2, .y =  1},
        {.x =  0, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  1}, {.x = -1, .y = -2},
        {.x =  0, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y = -1}, {.x =  1, .y =  2},
        {.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y = -2}, {.x = -2, .y =  1},
        {.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  2}, {.x =  2, .y = -1}
};

void LowrisChangeBoard(bool add, lowris_board *board, lowris_current_tetromino *current, int32_t xpos, int32_t ypos);
void LowrisUpdateCurrentTetromino(lowris_board *board, lowris_current_tetromino *current, SDL_Renderer *renderer);

#endif //LOWRIS_TETROMINO_H
