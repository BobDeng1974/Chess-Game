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

#include "Pawn.hpp"
#include "CellVerifier.hpp"
#include "Cell.hpp"

#define USER 1
#define OPPONENT 2
#define KING_LOS 3

class BoardVerifier
{
    public:
        enum State{STATE_CHECK, STATE_CHECKMATE, STATE_STALEMATE, STATE_NOTHING};
        BoardVerifier();
    
        State verifyBoardState( std::vector<Cell>& board, int turn);
    
        std::queue<int> getPieceMoves(int index);
    
        bool isCastleMove(int index) const;
    
    private:
        void rookAreaOfEffect(int row, int col);
        void knightAreaOfEffect(int row, int col);
        void bishopAreaOfEffect(int row, int col);
        void pawnAreaOfEffect(int row, int col);
        void kingAreaOfEffect(int row, int col);
        void verifyCastle();
        bool UpdateUserPieceMoves();
    
        static const int boardSize = 8;
        std::vector<CellVerifier> board_;
    
        std::queue<int> piecesQueue_;
        std::queue<int> piecesUserQueue_;
        std::queue<int> kingThreats_;
        std::queue<int> kingBlockers_;
    
    
        bool verifyKingState();
        State state_;               //reset
        int kingIndex_;             //reset
        Piece* king_ = nullptr;     //reset
        bool onlyKingMoves=false;   //reset
        int currentTurn;

};

#endif /* boardVerifier_hpp */// Show error message
