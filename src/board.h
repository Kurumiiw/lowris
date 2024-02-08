//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#ifndef LOWRIS_BOARD_H
#define LOWRIS_BOARD_H

#include <stdlib.h>
#include <SDL.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define TILE_SIZE 32

#define BOARD(x, y) ((x) + (y) * BOARD_WIDTH)

typedef struct {
    char *data;
} lowris_board;

lowris_board* LowrisCreateBoard();
void LowrisDrawBoard(lowris_board *board, SDL_Renderer *renderer, int32_t xpos, int32_t ypos);

#endif //LOWRIS_BOARD_H
