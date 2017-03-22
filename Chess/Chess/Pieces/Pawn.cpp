//
//  Pawn.cpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Pawn.hpp"

Pawn::Pawn(bool isPlayerControlled) : Piece(isPlayerControlled)
{
    this->type_ = CellTexture::PIECE_PAWN;
}

void Pawn::reset()
{
    Piece::reset();
    this->didDouble_ = -1;
}

int Pawn::getDoubleJumpTurn() const { return didDouble_; }

void Pawn::setDoubleJumpTurn(int turn){ this->didDouble_= turn; }
