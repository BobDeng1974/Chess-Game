//
//  Pawn.hpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include "Piece.hpp"

class Pawn : public Piece
{
    public:
        Pawn(bool isPlayerControlled);
    
        // Reset Pawn
        virtual void reset();
    
        // Getter
        int getDoubleJumpTurn() const;

        //Setters
        void setDoubleJumpTurn(int turn);
    
    private:
        int didDouble_;   // if piece pawn has done a double step
};



#endif /* Pawn_hpp */
