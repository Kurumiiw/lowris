#include <SDL.h>
#include <stdbool.h>

#include "board.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
} lowris_state;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    lowris_state state;

    state.running = true;

    state.window = SDL_CreateWindow(
            "lowris",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            0
            );

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    lowris_board *board = LowrisCreateBoard();

    board->data[1 + 2 * BOARD_WIDTH] = 1;
    board->data[2 + 2 * BOARD_WIDTH] = 2;
    board->data[3 + 2 * BOARD_WIDTH] = 3;
    board->data[4 + 2 * BOARD_WIDTH] = 4;
    board->data[5 + 2 * BOARD_WIDTH] = 5;
    board->data[6 + 2 * BOARD_WIDTH] = 6;
    board->data[7 + 2 * BOARD_WIDTH] = 7;

    while(state.running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) state.running = false;
        }

        SDL_SetRenderDrawColor(state.renderer, 95, 95, 95, 255);
        SDL_RenderClear(state.renderer);

        LowrisDrawBoard(board, state.renderer, 480, 40);

        SDL_RenderPresent(state.renderer);
    }

    SDL_DestroyWindow(state.window);
    SDL_DestroyRenderer(state.renderer);
    SDL_Quit();
    return 0;
}
