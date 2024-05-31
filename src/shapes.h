//
// Created by Ola Horg Jacobsen on 28/05/2024.
//

#ifndef LOWRIS_SHAPES_H
#define LOWRIS_SHAPES_H

#define IS_PLACED 128
#define SHAPE_WIDTH 4
#define SHAPE_HEIGHT 2
#define SHAPE_STRIDE (SHAPE_WIDTH * SHAPE_HEIGHT)
#define SHAPE_COORD(x, y, piece) shapes[x + (SHAPE_WIDTH * y) + shape_get_offset(piece) * SHAPE_STRIDE]

int shape_get_internal_offset(int piece)
{
    return (int)log2(piece);
}

typedef struct {
    int32_t x;
    int32_t y;
} lowris_kicktable_entry;

const char access_matrix[] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        4, 0, 5, 1, 6, 2, 7, 3,
        7, 6, 5, 4, 3, 2, 1, 0,
        3, 7, 2, 6, 1, 5, 0, 4
};

const char shapes[] = {
        0, 0, 0, 0,
        1, 1, 1, 1,

        2, 0, 0, 0,
        2, 2, 2, 0,

        0, 0, 4, 0,
        4, 4, 4, 0,

        0, 8, 8, 0,
        0, 8, 8, 0,

        0, 16, 16, 0,
        16, 16, 0, 0,

        0, 32, 0, 0,
        32, 32, 32, 0,

        64, 64, 0, 0,
        0, 64, 64, 0
};

static const lowris_kicktable_entry srs_ljstz_table[40] = {
           /* TEST 1  */       /* TEST 2  */       /* TEST 3 */        /* TEST 4  */       /* TEST 5  */
/*0->1*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y =  1}, {.x =  0, .y = -2}, {.x = -1, .y = -2},
/*1->0*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y = -1}, {.x =  0, .y =  2}, {.x =  1, .y =  2},
/*1->2*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y = -1}, {.x =  0, .y =  2}, {.x =  1, .y =  2},
/*2->1*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y =  1}, {.x =  0, .y = -2}, {.x = -1, .y = -2},
/*2->3*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y =  1}, {.x =  0, .y = -2}, {.x =  1, .y = -2},
/*3->2*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y = -1}, {.x =  0, .y =  2}, {.x = -1, .y =  2},
/*3->0*/{.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x = -1, .y = -1}, {.x =  0, .y =  2}, {.x = -1, .y =  2},
/*0->3*/{.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x =  1, .y =  1}, {.x =  0, .y = -2}, {.x =  1, .y = -2}
};

static const lowris_kicktable_entry srs_i_table[40] = {
                             /* ?? */
        {.x =  0, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y = -1}, {.x =  1, .y =  2},
        {.x =  0, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  1}, {.x = -1, .y = -2},
        {.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  2}, {.x =  2, .y = -1},
        {.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y = -2}, {.x = -2, .y =  1},
        {.x =  0, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  1}, {.x = -1, .y = -2},
        {.x =  0, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y = -1}, {.x =  1, .y =  2},
        {.x =  0, .y =  0}, {.x =  1, .y =  0}, {.x = -2, .y =  0}, {.x =  1, .y = -2}, {.x = -2, .y =  1},
        {.x =  0, .y =  0}, {.x = -1, .y =  0}, {.x =  2, .y =  0}, {.x = -1, .y =  2}, {.x =  2, .y = -1}
};

#endif //LOWRIS_SHAPES_H
