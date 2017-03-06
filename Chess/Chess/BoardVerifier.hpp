//
//  boardVerifier.hpp
//  Chess
//
//  Created by Ricardo Martins on 05/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef BoardVerifier_hpp
#define BoardVerifier_hpp

#include <iostream>
#include <vector>
#include <queue>

#include "Cell.hpp"
#include "Piece.hpp"

#define USER 1
#define OPPONENT 2

class BoardVerifier
{
    public:
        enum State{STATE_CHECK, STATE_CHECKMATE, STATE_STALEMATE, STATE_NOTHING};
        BoardVerifier();
    
        State verifyBoardState( std::vector<Cell>& board);
    
    private:
        void rookAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board);
        void knightAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board);
        void bishopAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board);
        void pawnAreaOfEffect(int row, int col, int teamValue);
    
        static const int boardSize = 8;
        int board_[boardSize][boardSize];
    
        std::queue<std::pair<int, int>> piecesQueue_;
    
        bool verifyKingState(SDL_Point kingCoords);
        State state_;
};

#endif /* boardVerifier_hpp */// Show error message
