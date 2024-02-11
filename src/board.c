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
            SDL_Rect current = { .h = TILE_SIZE, .w = TILE_SIZE, .x = xpos + x * TILE_SIZE, .y = ypos + y * TILE_SIZE};

            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &current);

            switch(board->data[x + BOARD_WIDTH * y])
            {
                case 1:
                case 10:
                    SDL_SetRenderDrawColor(renderer, 123, 255, 255, 255);
                    goto draw;
                case 2:
                case 20:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 123, 255);
                    goto draw;
                case 3:
                case 30:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                    goto draw;
                case 4:
                case 40:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    goto draw;
                case 5:
                case 50:
                    SDL_SetRenderDrawColor(renderer, 255, 123, 0, 255);
                    goto draw;
                case 6:
                case 60:
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    goto draw;
                case 7:
                case 70:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                draw:
                    SDL_RenderFillRect(renderer, &current);
                    break;

                default: break;
            }
        }
    }
}