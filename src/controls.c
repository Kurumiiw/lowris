//
// Created by Ola Horg Jacobsen on 11/02/2024.
//

#include "controls.h"

bool LowrisMoveCurrentPieceLeft(lowris_state *state, lowris_board *board)
{
    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(board->data[BOARD(state->current_piece->x + x, state->current_piece->y + y)] < 10)
                continue; //current tile is not a player tile, continue

            if(board->data[BOARD(state->current_piece->x + x, state->current_piece->y + y)] > 9)
            {
                if(state->current_piece->x + x - 1 < 0)
                    return false; // cannot move left, we are the leftmost possible


                if(board->data[BOARD(state->current_piece->x + x - 1, state->current_piece->y + y)] < 9
                   && board->data[BOARD(state->current_piece->x + x - 1, state->current_piece->y + y)] > 0)
                    return false; // cannot move left, something is blocking

            }
        }
    }

    state->current_piece->x--;
    return true;
}

bool LowrisMoveCurrentPieceRight(lowris_state *state, lowris_board *board)
{
    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for(int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            if(board->data[BOARD(state->current_piece->x + x, state->current_piece->y + y)] < 10)
                continue; //current tile is not a player tile, continue
            else
            {
                if(state->current_piece->x + x + 1 >= BOARD_WIDTH)
                    return false; // cannot move right, we are the rightmost possible

                if(board->data[BOARD(state->current_piece->x + x + 1, state->current_piece->y + y)] < 9
                   && board->data[BOARD(state->current_piece->x + x + 1, state->current_piece->y + y)] > 0)
                    return false; // cannot move right, something is blocking

            }
        }
    }

    state->current_piece->x++;
    return true;
}

bool LowrisMoveCurrentPieceLeftmost(lowris_state *state, lowris_board *board)
{
    int32_t hit  = -1;
    int32_t true_x = INT32_MAX;
    int32_t hit_x  = INT32_MAX;

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for (int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            int32_t current_x = state->current_piece->x + x;
            int32_t current_y = state->current_piece->y + y;

            if(board->data[BOARD(current_x, current_y)] < 10)
                continue; //not a player tile, continue
            else
            {
                true_x = x < true_x? x : true_x;

                if(current_x == 0)
                    return false; // cannot move left, we are the leftmost possible


                for(int32_t scan = current_x; scan > -1; scan--)
                {
                    if(board->data[BOARD(scan, current_y)] < 9
                    && board->data[BOARD(scan, current_y)] > 0)
                        if(scan >= hit)
                        {
                            hit = scan;
                            hit_x = x < hit_x? x : hit_x;
                        }
                }
            }
        }
    }

    state->current_piece->x = hit == -1 ? 0 - true_x : hit + 1 - hit_x;

    return true;
}

bool LowrisMoveCurrentPieceRightmost(lowris_state *state, lowris_board *board)
{
    int32_t hit    = INT32_MAX;
    int32_t hit_x  = 0;
    int32_t true_x = 0;

    for(int32_t y = 0; y < TETROMINO_HEIGHT; y++)
    {
        for (int32_t x = 0; x < TETROMINO_WIDTH; x++)
        {
            int32_t current_x = state->current_piece->x + x;
            int32_t current_y = state->current_piece->y + y;

            if(board->data[BOARD(current_x, current_y)] < 10)
                continue; //not a player tile, continue
            else
            {
                true_x = x > true_x? x : true_x;

                if(current_x + 1 >= BOARD_WIDTH)
                    return false; // cannot move right, we are the rightmost possible

                for(int32_t scan = current_x; scan < BOARD_WIDTH; scan++)
                {
                    if(board->data[BOARD(scan, current_y)] < 9
                    && board->data[BOARD(scan, current_y)] > 0)
                        if(scan <= hit)
                        {
                            hit = scan;
                            hit_x = x > hit_x? x : hit_x;
                        }
                }
            }
        }
    }

    state->current_piece->x = hit == INT32_MAX? BOARD_WIDTH - 1 - true_x : hit - 1 - hit_x;
    return true;
}