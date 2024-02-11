//
// Created by Ola Horg Jacobsen on 11/02/2024.
//

#ifndef LOWRIS_CONTROLS_H
#define LOWRIS_CONTROLS_H

#include <stdbool.h>
#include "board.h"
#include "structs.h"

bool LowrisMoveCurrentPieceLeft(lowris_state *state, lowris_board *board);
bool LowrisMoveCurrentPieceLeftmost(lowris_state *state, lowris_board *board);

bool LowrisMoveCurrentPieceRightmost(lowris_state *state, lowris_board *board);
bool LowrisMoveCurrentPieceRight(lowris_state *state, lowris_board *board);


#endif //LOWRIS_CONTROLS_H
