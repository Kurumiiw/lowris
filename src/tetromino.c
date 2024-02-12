//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#include "tetromino.h"

char* LowrisTetrominoShape(lowris_current_tetromino *current)
{
    switch (current->tetromino)
    {
        case I:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {0, 0, 0, 0,
                                     10, 10, 10, 10,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 0, 10, 0,
                                     0, 0, 10, 0,
                                     0, 0, 10, 0,
                                     0, 0, 10, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      0, 0, 0, 0,
                                      10, 10, 10, 10,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {0, 10, 0, 0,
                                      0, 10, 0, 0,
                                      0, 10, 0, 0,
                                      0, 10, 0, 0};
                default:
                    break;
            }
            break;
        case O:
            return (char[]) {20, 20, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        case T:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {0, 30, 0, 0,
                                      30, 30, 30, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 30, 0, 0,
                                      0, 30, 30, 0,
                                      0, 30, 0, 0,
                                      0, 0, 0, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      30, 30, 30, 0,
                                      0, 30, 0, 0,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {0, 30, 0, 0,
                                      30, 30, 0, 0,
                                      0, 30, 0, 0,
                                      0, 0, 0, 0};
                default:
                    break;
            }
            break;
        case J:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {40, 0, 0, 0,
                                      40, 40, 40, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 40, 40, 0,
                                      0, 40, 0, 0,
                                      0, 40, 0, 0,
                                      0, 0, 0, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      40, 40, 40, 0,
                                      0, 0, 40, 0,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {0, 40, 0, 0,
                                      0, 40, 0, 0,
                                      40, 40, 0, 0,
                                      0, 0, 0, 0};
                default:
                    break;
            }
            break;
        case L:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {0, 0, 50, 0,
                                      50, 50, 50, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 50, 0, 0,
                                      0, 50, 0, 0,
                                      0, 50, 50, 0,
                                      0, 0, 0, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      50, 50, 50, 0,
                                      50, 0, 0, 0,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {50, 50, 0, 0,
                                      0, 50, 0, 0,
                                      0, 50, 0, 0,
                                      0, 0, 0, 0};
                default:
                    break;
            }
            break;
        case S:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {0, 60, 60, 0,
                                      60, 60, 0, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 60, 0, 0,
                                      0, 60, 60, 0,
                                      0, 0, 60, 0,
                                      0, 0, 0, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      0, 60, 60, 0,
                                      60, 60, 0, 0,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {60, 0, 0, 0,
                                      60, 60, 0, 0,
                                      0, 60, 0, 0,
                                      0, 0, 0, 0};
                default:
                    break;
            }
            break;
        case Z:
            switch (current->rotation)
            {
                case 0:
                    return (char[]) {70, 70, 0, 0,
                                      0, 70, 70, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0};
                case 1:
                    return (char[]) {0, 0, 70, 0,
                                      0, 70, 70, 0,
                                      0, 70, 0, 0,
                                      0, 0, 0, 0};
                case 2:
                    return (char[]) {0, 0, 0, 0,
                                      70, 70, 0, 0,
                                      0, 70, 70, 0,
                                      0, 0, 0, 0};
                case 3:
                    return (char[]) {0, 70, 0, 0,
                                      70, 70, 0, 0,
                                      70, 0, 0, 0,
                                      0, 0, 0, 0};
                default:
                    break;
            }
            break;
    }

    return NULL;
}

// The new rotation state MUST be set in the lowris_current_tetromino as the "rotation" member.
void LowrisRotateTetromino(lowris_current_tetromino *current, lowris_board *board, bool add, int32_t xpos, int32_t ypos)
{
    if(!add)
    {
        for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
        {
            for (int32_t x = 0; x < TETROMINO_WIDTH; x++)
            {
                if (board->data[BOARD(xpos + x, ypos + y)] > 9)
                    board->data[BOARD(xpos + x, ypos + y)] = 0;
            }
        }

        return;
    }

    // See if there is nothing obstructing the rotation
    bool needs_kicktable = false;

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        if(needs_kicktable)
            break;

        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(board->data[BOARD(xpos + x, ypos + y)] < 10
            && board->data[BOARD(xpos + x, ypos + y)] > 0 )
            {
                needs_kicktable = true;
                break;
            }
        }
    }

    char* shape = LowrisTetrominoShape(current);

    if(needs_kicktable && current->rotation != current->last_rot)
    {
        return;
    }

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(shape[TETR(x, y)] != 0) board->data[BOARD(xpos + x, ypos + y)] = shape[TETR(x, y)];
        }
    }
}

void LowrisChangeBoard(bool add, lowris_board *board, lowris_current_tetromino *current, int32_t xpos, int32_t ypos)
{
    char* shape = LowrisTetrominoShape(current);

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
    LowrisRotateTetromino(current, board, false, current->last_x, current->last_y);
    LowrisRotateTetromino(current, board, true, current->x, current->y);

    //LowrisChangeBoard(false, board, current, current->last_x, current->last_y);
    //LowrisChangeBoard(true, board, current, current->x, current->y);

    current->last_x = current->x;
    current->last_y = current->y;
    current->last_rot = current->rotation;
}