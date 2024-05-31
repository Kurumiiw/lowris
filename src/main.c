#include <SDL.h>
#include <stdbool.h>
#include "shapes.h"

typedef enum {
    I = 1,
    J = 1 << 1,
    L = 1 << 2,
    O = 1 << 3,
    S = 1 << 4,
    T = 1 << 5,
    Z = 1 << 6
} piece;

typedef struct {
    int x, y, w, h;
    int rot;
    piece piece;
} player_s;

bool RUNNING = true;
bool DEBUG = true;

char *BOARD;

player_s player = { .x = 3,
                    .y = 2,
                    .w = 4,
                    .h = 2,
                  .rot = 0,
                .piece = I};

int player_shape_offset();

#define BOARD_X      (640 - (SIZE / 2) * BOARD_WIDTH)
#define BOARD_Y      45
#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20
#define SIZE         32
#define C(x, y) ((x) + ((y) * BOARD_WIDTH))
#define COORD(x, y) BOARD[C(x, y)]

bool srs_test(int previous_rot)
{
    if(DEBUG) printf("[SRS] Tests triggered...\n");

    int test_case = 0;

    switch(previous_rot)
    {
        default:
        case 0: switch(player.rot) {
                case 1: test_case = 0; break;
                case 3: test_case = 7; break;
            } break;
        case 1: switch(player.rot) {
                case 2: test_case = 2; break;
                case 0: test_case = 1; break;
            } break;
        case 2: switch(player.rot) {
                case 3: test_case = 4; break;
                case 1: test_case = 3; break;
            } break;
        case 3: switch(player.rot) {
                case 0: test_case = 6; break;
                case 2: test_case = 5; break;
            } break;
    }

    int test_base = test_case * 5;
    lowris_kicktable_entry test;

    int player_shape_offset_ = player_shape_offset();

    for(int i = 0; i < 5; i++)
    {
        if(DEBUG) printf("-> Running test %i\n", i + 1);

        switch (player.piece)
        {
            default:    test = srs_ljstz_table[test_base + i]; break;
            case I:     test = srs_i_table[test_base + i]; break;
        }

        int count = 0;
        int x_extent = player.rot % 2 == 1 ? SHAPE_HEIGHT : SHAPE_WIDTH;
        int y_extent = player.rot % 2 == 1 ? SHAPE_WIDTH : SHAPE_HEIGHT;

        bool blocked = false;
        for(int y = 0; y < y_extent; y++)
        {
            for(int x = 0; x < x_extent; x++)
            {
                char player_shape = shapes[shape_get_internal_offset(player.piece) * SHAPE_WIDTH * SHAPE_HEIGHT + access_matrix[count + player_shape_offset_]];
                if(player_shape)
                {
                    if(COORD(player.x + x + test.x, player.y + y + test.y) < 0)
                    {
                        if(DEBUG) printf("    -> Failure\n");
                        blocked = true;
                    }
                }

                if(blocked) break;

                count++;
            }

            if(blocked) break;
        }

        if(!blocked)
        {
            if(DEBUG) printf("    -> Success\n");

            player.x += test.x;
            player.y += test.y;

            return true;
        }
        else if(i == 4)
        {
            return false;
        }
    }

    return true;
}

void draw_board(SDL_Renderer *r)
{
    for(int x = 0; x < BOARD_WIDTH; x++)
    {
        for(int y = 0; y < BOARD_HEIGHT; y++)
        {
            SDL_Rect rect = {.x = SIZE * x + BOARD_X, .y = SIZE * y + BOARD_Y, .w = SIZE, .h = SIZE};

            SDL_SetRenderDrawColor(r, 150, 150, 150, 255);
            SDL_RenderDrawRect(r, &rect);

            char value = BOARD[C(x, y)];

            if(value & IS_PLACED) value -= (char)IS_PLACED;

            switch(value)
            {
                case I:  SDL_SetRenderDrawColor(r, 0, 204, 255, 255); break;
                case J:  SDL_SetRenderDrawColor(r, 0,   0, 204, 255); break;
                case L:  SDL_SetRenderDrawColor(r, 255, 102, 0, 255); break;
                case O:  SDL_SetRenderDrawColor(r, 255, 255, 0, 255); break;
                case S:  SDL_SetRenderDrawColor(r, 102, 255, 102, 255); break;
                case T:  SDL_SetRenderDrawColor(r, 153, 51, 255, 255); break;
                case Z:  SDL_SetRenderDrawColor(r, 255, 0, 102, 255); break;
                default: SDL_SetRenderDrawColor(r, 255, 255, 255, 255); break;
            }

            if(COORD(x, y) != 0) SDL_RenderFillRect(r, &rect);
        }
    }

    if(DEBUG)
    {
        SDL_Rect rect = {.x = player.x * SIZE + BOARD_X, .y = player.y * SIZE + BOARD_Y, .w = player.w * SIZE, .h = player.h * SIZE};

        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        SDL_RenderDrawRect(r, &rect);
    }
}

void player_update()
{
    // Clear board of player tiles

    for(int x = 0; x < BOARD_WIDTH; x++)
    {
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            if(COORD(x, y) > 0) COORD(x, y) = 0;
        }
    }

    int count = 0;
    int x_extent = player.rot % 2 == 1 ? SHAPE_HEIGHT : SHAPE_WIDTH;
    int y_extent = player.rot % 2 == 1 ? SHAPE_WIDTH : SHAPE_HEIGHT;

    for(int y = 0; y < y_extent; y++)
    {
        for(int x = 0; x < x_extent; x++)
        {
            int offset = player_shape_offset();

            char player_shape = shapes[shape_get_internal_offset(player.piece) * SHAPE_WIDTH * SHAPE_HEIGHT + access_matrix[count + offset]];
            if(player_shape)
                COORD(player.x + x, player.y + y) = player_shape;

            count++;
        }
    }
}

int player_shape_offset()
{
    int offset = 0;

    switch(player.rot)
    {
        case 1:
            offset = 8;
            break;
        case 2:
            offset = 16;
            break;
        case 3:
            offset = 24;
            break;
    }

    return offset;
}

void player_try_movement(int delta_x, int delta_y)
{
    if(DEBUG) printf("[PLAYER] Position (%i, %i)\n", player.x, player.y);
}

void player_try_rotation(int dir)
{
    int previous_rot = player.rot;
    player.rot = (player.rot + dir) % 4;
    if(player.rot < 0) player.rot = 3;

    int delta_x = 0;
    int delta_y = 0;

    switch(player.piece)
    {
        case O:
        case I: switch(previous_rot) {
            default:
            case 0:
                delta_x++; delta_y--;
                break;
            case 1:
                delta_x--; delta_y++;
                break;
            case 2:
                delta_x++; delta_y--;
                break;
            case 3:
                delta_x--; delta_y++;
                break;
        } break;

        case Z:
        case T:
        case S:
        case L:
        case J:switch(previous_rot) {
            default:
            case 0:
                if(player.rot == 1) delta_x++;
                if(player.rot == 3) delta_y--;
                break;
            case 1:
                if(player.rot == 0) delta_x--;
                if(player.rot == 2) {delta_x -= 2; delta_y++;}
                break;
            case 2:
                if(player.rot == 1) {delta_x += 2; delta_y--;}
                if(player.rot == 3) {delta_x++; delta_y -= 2;}
                break;
            case 3:
                if(player.rot == 2) {delta_x--; delta_y += 2;}
                if(player.rot == 0) delta_y++;
                break;
        } break;
    }

    player.x += delta_x;
    player.y += delta_y;

    if(!srs_test(previous_rot))
    {
        player.x -= delta_x;
        player.y -= delta_y;
        player.rot = previous_rot;

        return;
    }

    if(player.rot % 2)
    {
        player.w = 2;
        player.h = 4;
    }
    else
    {
        player.w = 4;
        player.h = 2;
    }



    player_update();

    if(DEBUG) printf("[PLAYER] Rotation %i\n", player.rot);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
            "lowris",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            0
            );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    BOARD = calloc(BOARD_WIDTH * BOARD_HEIGHT, 1);
    player_update();

    BOARD[44] = (char)(I | IS_PLACED);

    while(RUNNING)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) RUNNING = false;

            if(e.type == SDL_KEYDOWN && !e.key.repeat)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        RUNNING = false;
                        break;

                    case SDLK_RIGHT:
                        player_try_movement(1, 0);
                        break;

                    case SDLK_r:
                        player_try_rotation(1);
                        break;

                    case SDLK_q:
                        player_try_rotation(-1);
                        break;

                    case SDLK_w:
                        player_try_rotation(1);
                        player_try_rotation(1);
                        break;
                }

                if(DEBUG)
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_1:
                            player.piece = I;
                            break;
                        case SDLK_2:
                            player.piece = J;
                            break;
                        case SDLK_3:
                            player.piece = L;
                            break;
                        case SDLK_4:
                            player.piece = O;
                            break;
                        case SDLK_5:
                            player.piece = S;
                            break;
                        case SDLK_6:
                            player.piece = T;
                            break;
                        case SDLK_7:
                            player.piece = Z;
                            break;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 95, 95, 95, 255);
        SDL_RenderClear(renderer);

        draw_board(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}