//
// Created by Ola Horg Jacobsen on 11/02/2024.
//

#ifndef LOWRIS_STRUCTS_H
#define LOWRIS_STRUCTS_H

#include <SDL.h>
#include "tetromino.h"

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

#endif //LOWRIS_STRUCTS_H
