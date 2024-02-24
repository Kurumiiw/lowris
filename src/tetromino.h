//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#ifndef LOWRIS_TETROMINO_H
#define LOWRIS_TETROMINO_H

#include <stdbool.h>
#include "structs.h"
#include "board.h"

#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 4

#define TETR(x, y) ((x) + (y) * TETROMINO_WIDTH)

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

static const char shapes[] = {
        // -- I --
         0,  0,  0,  0,
        10, 10, 10, 10,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0,  0, 10,  0,
         0,  0, 10,  0,
         0,  0, 10,  0,
         0,  0, 10,  0,

         0,  0,  0,  0,
         0,  0,  0,  0,
        10, 10, 10, 10,
         0,  0,  0,  0,

         0, 10,  0,  0,
         0, 10,  0,  0,
         0, 10,  0,  0,
         0, 10,  0,  0,

        // -- T --

         0, 30,  0,  0,
        30, 30, 30,  0,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0, 30,  0,  0,
         0, 30, 30,  0,
         0, 30,  0,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
        30, 30, 30,  0,
         0, 30,  0,  0,
         0,  0,  0,  0,

         0, 30,  0,  0,
        30, 30,  0,  0,
         0, 30,  0,  0,
         0,  0,  0,  0,

        // -- J --

        40,  0,  0,  0,
        40, 40, 40,  0,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0, 40, 40,  0,
         0, 40,  0,  0,
         0, 40,  0,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
        40, 40, 40,  0,
         0,  0, 40,  0,
         0,  0,  0,  0,

         0, 40,  0,  0 ,
         0, 40,  0,  0,
        40, 40,  0,  0,
         0,  0,  0,  0,

         // -- L --

         0,  0, 50,  0,
        50, 50, 50,  0,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0, 50,  0,  0,
         0, 50,  0,  0,
         0, 50, 50,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
        50, 50, 50,  0,
        50,  0,  0,  0,
         0,  0,  0,  0,

        50, 50,  0,  0,
         0, 50,  0,  0,
         0, 50,  0,  0,
         0,  0,  0,  0,

        // -- S --

         0, 60, 60,  0,
        60, 60,  0,  0,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0, 60,  0,  0,
         0, 60, 60,  0,
         0,  0, 60,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
         0, 60, 60,  0,
        60, 60,  0,  0,
         0,  0,  0,  0,

        60,  0,  0,  0,
        60, 60,  0,  0,
         0, 60,  0,  0,
         0,  0,  0,  0,

        // -- Z --

        70, 70,  0,  0,
         0, 70, 70,  0,
         0,  0,  0,  0,
         0,  0,  0,  0,

         0,  0, 70,  0,
         0, 70, 70,  0,
         0, 70,  0,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
        70, 70,  0,  0,
         0, 70, 70,  0,
         0,  0,  0,  0,

         0,  0,  0,  0,
        70, 70,  0,  0,
         0, 70, 70,  0,
         0,  0,  0,  0
};

char* LowrisTetrominoShape(lowris_current_tetromino *current);
bool LowrisSRSTest(lowris_current_tetromino *current, lowris_kicktable_entry entry, lowris_board *board);
void LowrisRotateTetromino(lowris_current_tetromino *current, lowris_board *board, bool add, int32_t xpos, int32_t ypos);
void LowrisChangeBoard(bool add, lowris_board *board, lowris_current_tetromino *current, int32_t xpos, int32_t ypos);
void LowrisUpdateCurrentTetromino(lowris_board *board, lowris_current_tetromino *current, SDL_Renderer *renderer);
void LowrisCheckPlaceTetromino(lowris_state *state, lowris_board *board);
#endif //LOWRIS_TETROMINO_H
