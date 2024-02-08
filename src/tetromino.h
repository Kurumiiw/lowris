//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#ifndef LOWRIS_TETROMINO_H
#define LOWRIS_TETROMINO_H

#include "board.h"

#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 2

#define TETR(x, y) ((x) + (y) * TETROMINO_WIDTH)

typedef struct {
    char shape[TETROMINO_WIDTH * TETROMINO_HEIGHT];
} lowris_tetromino;

typedef enum {
    I,
    O,
    T,
    J,
    L,
    S,
    Z
} lowris_tetrominoes;

void LowrisAddTetromino(lowris_board *board, lowris_tetrominoes type, int32_t xpos, int32_t ypos);

#endif //LOWRIS_TETROMINO_H
