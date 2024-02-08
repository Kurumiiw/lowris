#include <SDL.h>
#include <stdbool.h>

#include "board.h"
#include "tetromino.h"

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

    board->data[BOARD(1, 2)] = 1;
    board->data[BOARD(2, 2)] = 2;
    board->data[BOARD(3, 2)] = 3;
    board->data[BOARD(4, 2)] = 4;
    board->data[BOARD(5, 2)] = 5;
    board->data[BOARD(6, 2)] = 6;
    board->data[BOARD(7, 2)] = 7;

    LowrisAddTetromino(board, (lowris_tetrominoes)I, 0, 5);
    LowrisAddTetromino(board, (lowris_tetrominoes)O, 0, 7);
    LowrisAddTetromino(board, (lowris_tetrominoes)T, 0, 9);
    LowrisAddTetromino(board, (lowris_tetrominoes)J, 0, 11);
    LowrisAddTetromino(board, (lowris_tetrominoes)L, 0, 13);
    LowrisAddTetromino(board, (lowris_tetrominoes)S, 0, 15);
    LowrisAddTetromino(board, (lowris_tetrominoes)Z, 0, 17);

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
