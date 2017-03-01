//
//  King.hpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef King_hpp
#define King_hpp

#include "Piece.hpp"

class King : public Piece
{
    public:
        King(bool isPlayerControlled);
};

#endif /* King_hpp */
