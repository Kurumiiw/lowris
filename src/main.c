#include <SDL.h>
#include <stdbool.h>

#include "board.h"
#include "tetromino.h"
#include "ns.h"

typedef enum {
    LOWRIS_NONE     = 0,
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
    double repeat_timer_threshold;

    double repeat_wait_timer;
    double repeat_wait_threshold;

    lowris_keymap last_direction;

    bool right_down;
    bool left_down;
} lowris_state;

void LowrisMoveCurrentPieceLeft(lowris_state *state)
{
    if(state->current_piece->x > 0) state->current_piece->x--;
}

void LowrisMoveCurrentPieceRight(lowris_state *state)
{
    int32_t offset = state->current_piece->tetromino == I? 4 : 3;
    if(state->current_piece->x < (BOARD_WIDTH - offset)) state->current_piece->x++;
}

void LowrisMoveCurrentPieceLeftmost(lowris_current_tetromino *current, lowris_board *board)
{
    current->x = 0;
}

void LowrisMoveCurrentPieceRightmost(lowris_current_tetromino *current, lowris_board *board)
{
    int32_t offset = current->tetromino == I? 4 : 3;

    current->x = BOARD_WIDTH - offset;
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    lowris_state state;

    state.running = true;
    uint64_t last_frame = ns();
    bool right_down_last;
    bool left_down_last;

    state.window = SDL_CreateWindow(
            "lowris",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            0
            );

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    lowris_board *board = LowrisCreateBoard();

    // Current piece setup

    state.current_piece = &(lowris_current_tetromino){
        .tetromino = I,
        .x = 3, .last_x = 3,
        .y = 0, .last_y = 0
    };

    state.repeat_timer = 0;
    state.repeat_timer_threshold = 0;

    state.repeat_wait_timer = 0;
    state.repeat_wait_threshold = 87;

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
                switch ((lowris_keymap)e.key.keysym.sym)
                {
                    case LOWRIS_LEFT:
                        state.left_down = true;
                        break;
                    case LOWRIS_RIGHT:
                        state.right_down = true;
                        break;
                    case LOWRIS_SLOW:break;
                    case LOWRIS_ROT_CW:break;
                    case LOWRIS_ROT_CCW:break;
                    case LOWRIS_HARD:break;
                    case LOWRIS_HOLD:break;
                    case LOWRIS_ROT_180:break;
                    case LOWRIS_NONE:break;
                }
            }

            if(e.type == SDL_KEYUP)
            {
                switch ((lowris_keymap)e.key.keysym.sym)
                {
                    case LOWRIS_LEFT:
                        state.left_down = false;
                        break;
                    case LOWRIS_RIGHT:
                        state.right_down = false;
                        break;
                    case LOWRIS_SLOW:break;
                    case LOWRIS_HARD:break;
                    case LOWRIS_HOLD:break;
                    case LOWRIS_ROT_CW:break;
                    case LOWRIS_ROT_CCW:break;
                    case LOWRIS_ROT_180:break;
                    case LOWRIS_NONE:break;
                }
            }
        }

        // --- LOGIC

        // RIGHT was just pressed
        if(state.right_down && !right_down_last)
        {
            state.repeat_wait_timer = 0;
            state.repeat_timer = 0;

            LowrisMoveCurrentPieceRight(&state);
            state.last_direction = LOWRIS_RIGHT;
        }

        // LEFT was just pressed
        if(state.left_down && !left_down_last)
        {
            state.repeat_wait_timer = 0;
            state.repeat_timer = 0;

            LowrisMoveCurrentPieceLeft(&state);
            state.last_direction = LOWRIS_LEFT;
        }

        // both LEFT and RIGHT are being pressed
        if(state.left_down && state.right_down)
        {
            switch(state.last_direction)
            {
                case LOWRIS_LEFT:
                    goto LEFT_MOVEMENT_LOGIC;
                case LOWRIS_RIGHT:
                    goto RIGHT_MOVEMENT_LOGIC;
            }
        }
        //both are not being pressed, left is held down
        else if(state.left_down)
        {
            LEFT_MOVEMENT_LOGIC:
            state.repeat_wait_timer += delta_time;
            if(state.repeat_wait_timer > state.repeat_wait_threshold)
            {
                //CHECK speed setting
                LowrisMoveCurrentPieceLeftmost(state.current_piece, board);
            }
        }
        // oth are not being pressed, right is held down
        else if(state.right_down)
        {
            RIGHT_MOVEMENT_LOGIC:
            state.repeat_wait_timer += delta_time;
            if(state.repeat_wait_timer > state.repeat_wait_threshold)
            {
                //CHECK speed setting
                LowrisMoveCurrentPieceRightmost(state.current_piece, board);
            }
        }

        state.move_timer += delta_time;

        if(state.move_timer >= 500) //todo: update based on level
        {
            //state.current_piece->y += 1;

            state.move_timer = 0;
        }

        LowrisUpdateCurrentTetromino(board, state.current_piece, state.renderer);

        left_down_last = state.left_down;
        right_down_last = state.right_down;

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
