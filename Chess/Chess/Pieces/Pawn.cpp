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
    this->didDouble_ = false;
}

void Pawn::reset()
{
    Piece::reset();
    this->didDouble_ = false;
}

bool Pawn::didDouble() const { return didDouble_; }

void Pawn::setDouble(){ this->didDouble_=true; }
