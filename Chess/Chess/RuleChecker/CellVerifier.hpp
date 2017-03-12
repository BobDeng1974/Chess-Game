//
//  CellVerifier.hpp
//  Chess
//
//  Created by Ricardo Martins on 09/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef CellVerifier_hpp
#define CellVerifier_hpp

#include <SDL2/SDL.h>
#include <queue>
#include <vector>

#include "Pawn.hpp"

class CellVerifier
{
public:
    enum direction{DIR_N, DIR_NE, DIR_E, DIR_SE, DIR_S, DIR_SO, DIR_O, DIR_NO};
    
    CellVerifier(int row, int col);
    
    void reset();
    
    bool pruneMovements( std::vector<int> moves);
    void pruneProtectKingMovement();
    
    // Setters
    void setPiece( Piece* piece);
    void setMove(int index);
    void setReachable();
    void setProtectsKing(direction dir);
    
    // Getters
    bool isMovable() const;
    int getOwner() const;
    Piece* getPiece() const;
    bool getPassant(int turn) const;
    bool isReachable() const;
    bool isProtectingKing() const;
    std::queue<int> getMoves() const;
    
private:
    SDL_Point position_;
    Piece* piece_ = nullptr;
    
    std::queue<int> possibleMoves_;
    
    // State Variables
    bool reachable_ = false;
    bool protectsKing_ = false;
    direction protectDir;

};


#endif /* CellVerifier_hpp */
