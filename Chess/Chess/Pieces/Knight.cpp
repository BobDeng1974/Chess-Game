//
//  Knight.cpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Knight.hpp"

Knight::Knight(bool isPlayerControlled) : Piece(isPlayerControlled)
{
    this->type_ = CellTexture::PIECE_KNIGHT;
}
