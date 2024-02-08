//
// Created by Ola Horg Jacobsen on 08/02/2024.
//

#include "board.h"

lowris_board* LowrisCreateBoard()
{
    lowris_board *result = malloc(sizeof(lowris_board));

    result->data = calloc(10 * 20, 1);
    return result;
}

void LowrisDrawBoard(lowris_board *board, SDL_Renderer *renderer, int32_t xpos, int32_t ypos)
{
    for(int32_t y = 0; y < BOARD_HEIGHT; y++)
    {
        for(int32_t x = 0; x < BOARD_WIDTH; x++)
        {
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &(SDL_Rect){ .h = TILE_SIZE, .w = TILE_SIZE, .x = xpos + x * TILE_SIZE, .y = ypos + y * TILE_SIZE});
        }
    }
}