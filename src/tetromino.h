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
    I,
    O,
    T,
    J,
    L,
    S,
    Z
} lowris_tetrominoes;

typedef struct {
    int32_t x, last_x;
    int32_t y, last_y;

    int32_t rotation, last_rot;
    lowris_tetrominoes tetromino;
} lowris_current_tetromino;

void LowrisChangeBoard(bool add, lowris_board *board, lowris_current_tetromino *current, int32_t xpos, int32_t ypos);
void LowrisUpdateCurrentTetromino(lowris_board *board, lowris_current_tetromino *current, SDL_Renderer *renderer);

#endif //LOWRIS_TETROMINO_H
