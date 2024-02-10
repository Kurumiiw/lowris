#include <SDL.h>
#include <stdbool.h>

#include "board.h"
#include "tetromino.h"
#include "ns.h"

typedef enum {
    LOWRIS_LEFT     = SDLK_LEFT,
    LOWRIS_RIGHT    = SDLK_RIGHT,
    LOWRIS_SLOW     = SDLK_DOWN,
    LOWRIS_HARD     = SDLK_SPACE,
    LOWRIS_HOLD     = SDLK_LSHIFT,
    LOWRIS_ROT_CW   = SDLK_UP,
    LOWRIS_ROT_CCW  = SDLK_RSHIFT,
    LOWRIS_ROT_180  = SDLK_z
} lowris_keymap;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;

    lowris_current_tetromino *current_piece;
    double move_timer;
    double repeat_timer;

    lowris_keymap held_key;
    bool is_held;
} lowris_state;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    lowris_state state;

    state.running = true;
    uint64_t last_frame = ns();

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

    state.current_piece = &(lowris_current_tetromino){
        .tetromino = T,
        .x = 3, .last_x = 3,
        .y = 0, .last_y = 0
    };

    state.move_timer = 0;

    while(state.running)
    {
        uint64_t this_frame = ns();
        uint64_t fps = 1000000000 / (this_frame - last_frame);
        double delta_time = (double)(this_frame - last_frame) / 1000000.0;

        //printf("dt: %fms, fps: %llu\n", delta_time, fps);

        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) state.running = false;

            if(e.type == SDL_KEYDOWN)
            {
                if (!state.is_held)
                {
                    state.is_held = true;

                    //todo: repeat
                    switch ((lowris_keymap)e.key.keysym.sym)
                    {
                        case LOWRIS_LEFT:
                            state.current_piece->x -= 1;
                            break;
                        case LOWRIS_RIGHT:
                            state.current_piece->x += 1;
                            break;
                        case LOWRIS_SLOW:
                            break;
                        case LOWRIS_ROT_CW:
                            break;
                        case LOWRIS_ROT_CCW:
                            break;
                        case LOWRIS_HARD:
                            break;
                        case LOWRIS_HOLD:
                            break;
                        case LOWRIS_ROT_180:
                            break;
                    }
                    break;
                }
            }

            if(e.type == SDL_KEYUP)
            {
                state.is_held = false;
            }
        }

        // --- LOGIC

        state.move_timer += delta_time;

        if(state.is_held)
        {

        }

        if(state.move_timer >= 500) //todo: update based on level
        {
            state.current_piece->y += 1;

            state.move_timer = 0;
        }

        LowrisUpdateCurrentTetromino(board, state.current_piece, state.renderer);

        // --- RENDER

        SDL_SetRenderDrawColor(state.renderer, 95, 95, 95, 255);
        SDL_RenderClear(state.renderer);

        LowrisDrawBoard(board, state.renderer, 480, 40);

        SDL_RenderPresent(state.renderer);;

        last_frame = this_frame;
    }

    SDL_DestroyWindow(state.window);
    SDL_DestroyRenderer(state.renderer);
    SDL_Quit();
    return 0;
}
