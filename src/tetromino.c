//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#include "tetromino.h"
#include "structs.h"

void LowrisCheckPlaceTetromino(lowris_state *state, lowris_board *board)
{
    int32_t max_y = -1;
    lowris_current_tetromino *current = state->current_piece;

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(current->y + y > BOARD_HEIGHT)
                max_y = current->y;


            if(board->data[BOARD(current->x + x, current->y + y)] > 9)
            {
                if(board->data[BOARD(current->x + x, current->y + y + 1)] < 10
                && board->data[BOARD(current->x + x, current->y + y + 1)] > 0)
                {
                    if(current->y + y >= max_y)
                        max_y = current->y + y;

                }
            }
        }
    }

    if(max_y != -1)
    {
        for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
        {
            for (int32_t x = 0; x < TETROMINO_WIDTH; x++)
            {
                if(board->data[BOARD(current->x + x, current->y + y)] > 9)
                {
                    board->data[BOARD(current->x + x, current->y + y)] /= 10; //???
                }
            }
        }

        free(state->current_piece);
        state->current_piece = malloc(sizeof(lowris_current_tetromino));
        state->current_piece->tetromino = Z;
        state->current_piece->x = 3;
        state->current_piece->last_x = 3;
        state->current_piece->y = 2;
        state->current_piece->last_y = 2;
        state->current_piece->rotation = 0;
        state->current_piece->last_rot = 0;
    }
}

char* LowrisTetrominoShape(lowris_current_tetromino *current)
{
    if(current->tetromino == O) return (char[]) {20, 20, 0, 0, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    return (char*) &shapes[TETROMINO_WIDTH * TETROMINO_HEIGHT * current->rotation + (TETROMINO_HEIGHT * TETROMINO_WIDTH * 4 * current->tetromino)];
}

bool LowrisSRSTest(lowris_current_tetromino *current, lowris_kicktable_entry entry, lowris_board *board)
{
    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            char* shape = LowrisTetrominoShape(current);

            if(shape[TETR(x, y)] != 0)
            {
                if(current->x + x + entry.x < 0 || current->x + x + entry.x >= BOARD_WIDTH)
                    return false;

                if(board->data[BOARD(current->x + x + entry.x, current->y + y + entry.y)] != 0)
                    return false;
            }
        }
    }

    return true;
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

    char* shape = LowrisTetrominoShape(current);


    if(current->rotation != current->last_rot)
    {
        //rotation requires kicktable, we just rotated
        int32_t row = -1;
        if(current->last_rot == 0)
        {
            if(current->rotation == 1)  row = 0;
            else                        row = 7;
        }
        else if(current->last_rot == 1)
        {
            if (current->rotation == 0) row = 1;
            else                        row = 2;
        }
        else if(current->last_rot == 2)
        {
            if(current->rotation == 1)  row = 3;
            else                        row = 4;
        }
        else if(current->last_rot == 3)
        {
            if(current->rotation == 2)  row = 5;
            else                        row = 6;
        }

        for(int32_t column = 0; column < 6; column++)
        {
            int32_t index = row * 5 + column;

            lowris_kicktable_entry entry = current->tetromino == I? srs_i_table[index] : srs_ljstz_table[index];

            bool test = LowrisSRSTest(current, entry, board);

            if(test)
            {
                printf("SRS test %i succeeded\n", column);

                for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
                {
                    for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
                    {
                        if(shape[TETR(x, y)] != 0) board->data[BOARD(xpos + x + entry.x, ypos + y + entry.y)] = shape[TETR(x, y)];
                    }
                }

                current->x += entry.x;
                current->y += entry.y;

                return;
            }
            else
            {
                printf("SRS test %i failed\n", column);
            }
        }

        // abort rotation, no available rotations
        current->rotation = current->last_rot;
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