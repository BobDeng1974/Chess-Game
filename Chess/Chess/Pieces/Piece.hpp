//
//  Piece.hpp
//  Chess
//
//  Created by Ricardo Martins on 01/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

#include "CellTexture.hpp"

class Piece
{
    public:
        Piece(bool isPlayerControlled);
    
        // reset piece
        virtual void reset();
    
        // Setters
        void setMoved();
    
        // Getters
        bool hasMoved() const;
        bool isControlled() const;
        CellTexture::Piece getType() const;
    
    protected:
        // Piece type specific values
        CellTexture::Piece type_;
        int value_;
    
        // State Variables
        bool hasMoved_;         // If piece has moved
        bool isControlled_;     // if belongs to player or enemy
};
#endif /* Piece_hpp */
