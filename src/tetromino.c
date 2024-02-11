//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#include "tetromino.h"

void LowrisChangeBoard(bool add, lowris_board *board, lowris_current_tetromino *current, int32_t xpos, int32_t ypos)
{
    char* shape;

    switch(current->tetromino)
    {
        case I:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){0,   0,  0,  0,
                                     10, 10, 10, 10,
                                     0,   0,  0, 0,
                                     0,   0,  0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 0, 10, 0,
                                     0, 0, 10, 0,
                                     0, 0, 10, 0,
                                     0, 0, 10, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     0, 0, 0, 0,
                                     10, 10, 10, 10,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){0, 10, 0, 0,
                                     0, 10, 0, 0,
                                     0, 10, 0, 0,
                                     0, 10, 0, 0};
                    break;
                default:break;
            } break;
        case O:
            shape = (char[]){20, 20, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            break;
        case T:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){0, 30, 0, 0,
                                     30, 30, 30, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 30, 0, 0,
                                     0, 30, 30, 0,
                                     0, 30, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     30, 30, 30, 0,
                                     0, 30, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){0, 30, 0, 0,
                                     30, 30, 0, 0,
                                     0, 30, 0, 0,
                                     0, 0, 0, 0};
                    break;
                default:break;
            } break;
        case J:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){40, 0, 0, 0,
                                     40, 40, 40, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 40, 40, 0,
                                     0, 40, 0, 0,
                                     0, 40, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     40, 40, 40, 0,
                                     0, 0, 40, 0,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){0, 40, 0, 0,
                                     0, 40, 0, 0,
                                     40, 40, 0, 0,
                                     0, 0, 0, 0};
                    break;
                default:break;
            } break;
        case L:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){0, 0, 50, 0,
                                     50, 50, 50, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 50, 0, 0,
                                     0, 50, 0, 0,
                                     0, 50, 50, 0,
                                     0, 0, 0, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     50, 50, 50, 0,
                                     50, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){50, 50, 0, 0,
                                     0, 50, 0, 0,
                                     0, 50, 0, 0,
                                     0, 0, 0, 0};
                    break;
                default:break;
            } break;
        case S:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){0, 60, 60, 0,
                                     60, 60, 0, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 60, 0, 0,
                                     0, 60, 60, 0,
                                     0, 0, 60, 0,
                                     0, 0, 0, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     0, 60, 60, 0,
                                     60, 60, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){60, 0, 0, 0,
                                     60, 60, 0, 0,
                                     0, 60, 0, 0,
                                     0, 0, 0, 0};
                    break;
                default:break;
            } break;
        case Z:
            switch(current->rotation)
            {
                case 0:
                    shape = (char[]){70, 70, 0, 0,
                                     0, 70, 70, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 1:
                    shape = (char[]){0, 0, 70, 0,
                                     0, 70, 70, 0,
                                     0, 70, 0, 0,
                                     0, 0, 0, 0};
                    break;
                case 2:
                    shape = (char[]){0, 0, 0, 0,
                                     70, 70, 0, 0,
                                     0, 70, 70, 0,
                                     0, 0, 0, 0};
                    break;
                case 3:
                    shape = (char[]){0, 70, 0, 0,
                                     70, 70, 0, 0,
                                     70, 0, 0, 0,
                                     0, 0, 0, 0};
                    break;
                default:break;
            } break;
    }

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(add)
            {
                if(shape[TETR(x, y)] != 0) board->data[BOARD(xpos + x, ypos + y)] = shape[TETR(x, y)];
            }
            else if(board->data[BOARD(xpos + x, ypos + y)] > 9) board->data[BOARD(xpos + x, ypos + y)] = 0;
        }
    }
}

void LowrisUpdateCurrentTetromino(lowris_board *board, lowris_current_tetromino *current, SDL_Renderer *renderer)
{
    LowrisChangeBoard(false, board, current, current->last_x, current->last_y);
    LowrisChangeBoard(true, board, current, current->x, current->y);

    current->last_x = current->x;
    current->last_y = current->y;
}