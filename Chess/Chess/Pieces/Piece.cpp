//
//  Piece.cpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Piece.hpp"

Piece::Piece(bool isPlayerControlled)
{
    this->isControlled_ = isPlayerControlled;
    reset();
}

void Piece::reset()
{
    hasMoved_=false;
}

void Piece::setMoved() { this->hasMoved_ = true; }

bool Piece::isControlled() const { return isControlled_; }

bool Piece::hasMoved() const { return hasMoved_; }

CellTexture::Piece Piece::getType() const { return type_; }
