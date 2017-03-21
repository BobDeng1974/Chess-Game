//
//  CellVerifier.cpp
//  Chess
//
//  Created by Ricardo Martins on 09/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "CellVerifier.hpp"

CellVerifier::CellVerifier(int row, int col)
{
    position_.x = col;
    position_.y = row;
}

void
CellVerifier::reset()
{
    piece_ = nullptr;
    protectsKing_ = false;
    reachable_ = false;
    castleMove_=false;
    while(!possibleMoves_.empty())
        possibleMoves_.pop();
    attackDirection_.reset();
}

void
CellVerifier::pruneProtectKingMovement()
{
    std::queue<int> validMoves;
    if( protectsKing_){
        switch (protectDir) {
            case DIR_N:
            case DIR_S:
                while( !possibleMoves_.empty()){
                    int move = possibleMoves_.front();
                    possibleMoves_.pop();
                    if( move%8 == position_.x)
                        validMoves.push(move);
                }
                break;
                
            case DIR_E:
            case DIR_O:
                while( !possibleMoves_.empty()){
                    int move = possibleMoves_.front();
                    possibleMoves_.pop();
                    if( move/8 == position_.y)
                        validMoves.push(move);
                }
                break;
                
            case DIR_NE:
            case DIR_SO:
                while( !possibleMoves_.empty()){
                    int move = possibleMoves_.front();
                    possibleMoves_.pop();
                    if( (move%8 - position_.x) == (move/8 - position_.y)*-1)
                        validMoves.push(move);
                }
                break;
                
            case DIR_NO:
            case DIR_SE:
                while( !possibleMoves_.empty()){
                    int move = possibleMoves_.front();
                    possibleMoves_.pop();
                    if( (move%8 - position_.x) == (move/8 - position_.y))
                        validMoves.push(move);
                }
                break;
        }
    }
    possibleMoves_ = validMoves;
}

bool
CellVerifier::pruneMovements(std::vector<int> moves)
{
    std::queue<int> validMoves;

    while( !possibleMoves_.empty()){
        bool exists=false;
        int index = possibleMoves_.front();
        possibleMoves_.pop();
        for(int move: moves){
            if( move == index)
                exists=true;
        }
        if (exists) {
            validMoves.push(index);
        }
    }
    possibleMoves_ = validMoves;
    return !possibleMoves_.empty();
}


// Setters
void
CellVerifier::setPiece(Piece* piece){ this->piece_ = piece; }
void
CellVerifier::setMove(int index){ possibleMoves_.push(index); }
void
CellVerifier::setReachable(){ reachable_ = true; }
void
CellVerifier::setProtectsKing( direction dir )
{
    protectDir = dir;
    protectsKing_ = true;
}
void
CellVerifier::setAttackerDirection(CellVerifier::direction dir) { attackDirection_.set(dir%4); }
void
CellVerifier::setCastleMove(){ castleMove_=true;}
// Getters
bool
CellVerifier::isMovable() const{ return !possibleMoves_.empty(); }
int
CellVerifier::getOwner() const
{
    if (piece_ ==nullptr)
        return 0;
    else
        return (piece_->isControlled())? 1:2;
}
Piece*
CellVerifier::getPiece() const { return piece_; }
bool
CellVerifier::isReachable() const { return reachable_;}
bool
CellVerifier::getPassant(int turn) const
{
    if(piece_!=nullptr && piece_->getType()==CellTexture::PIECE_PAWN){
        Pawn* adjacent = static_cast<Pawn*>(piece_);
        return (turn - adjacent->getDoubleJumpTurn()==1)? true:false;
    }
    else
        return false;
}
bool
CellVerifier::isProtectingKing() const { return protectsKing_;}
std::queue<int>
CellVerifier::getMoves() const {  return possibleMoves_; }
bool
CellVerifier::isAttackedFromDirection(CellVerifier::direction dir) const { return attackDirection_[dir%4];}
bool
CellVerifier::isCastleMove() const { return castleMove_; }
