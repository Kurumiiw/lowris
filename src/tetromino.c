//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#include "tetromino.h"

void LowrisChangeBoard(bool add, lowris_board *board, lowris_tetrominoes type, int32_t xpos, int32_t ypos)
{
    char* shape;

    switch(type)
    {
        case I:
            shape = (char[]){1, 1, 1, 1, 0, 0, 0, 0};
            break;
        case O:
            shape = (char[]){2, 2, 0, 0, 2, 2, 0, 0};
            break;
        case T:
            shape = (char[]){3, 3, 3, 0, 0, 3, 0, 0};
            break;
        case J:
            shape = (char[]){4, 4, 4, 0, 0, 0, 4, 0};
            break;
        case L:
            shape = (char[]){0, 0, 5, 0, 5, 5, 5, 0};
            break;
        case S:
            shape = (char[]){0, 6, 6, 0, 6, 6, 0, 0};
            break;
        case Z:
            shape = (char[]){7, 7, 0, 0, 0, 7, 7, 0};
            break;
    }

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            board->data[BOARD(xpos + x, ypos + y)] = add? shape[TETR(x, y)] : 0;
        }
    }
}

void LowrisUpdateCurrentTetromino(lowris_board *board, lowris_current_tetromino *current, SDL_Renderer *renderer)
{
    LowrisChangeBoard(false, board, current->tetromino, current->last_x, current->last_y);
    LowrisChangeBoard(true, board, current->tetromino, current->x, current->y);

    current->last_x = current->x;
    current->last_y = current->y;
}