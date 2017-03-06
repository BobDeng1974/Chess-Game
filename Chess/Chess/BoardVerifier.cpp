//
//  boardVerifier.cpp
//  Chess
//
//  Created by Ricardo Martins on 05/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "BoardVerifier.hpp"

BoardVerifier::BoardVerifier(){}

BoardVerifier::State
BoardVerifier::verifyBoardState(std::vector<Cell> &board)
{
    SDL_Point king;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if( board[(i*boardSize)+j].getPiece()==nullptr){
                board_[i][j]=0;
            }else{
                board_[i][j] = ( board[(i*boardSize)+j].getPiece()->isControlled())? USER : OPPONENT;
                if( !board[(i*boardSize)+j].getPiece()->isControlled()){
                    if(board[(i*boardSize)+j].getPiece()->getType()==CellTexture::PIECE_KING)
                        king = {i,j};
                    else
                        piecesQueue_.push(std::pair<int, int>(i,j));
                }
            }
        }
    }

    while (!piecesQueue_.empty()) {
        std::pair<int, int> pieceCoords = piecesQueue_.front();
        piecesQueue_.pop();
        int row = pieceCoords.first;
        int col = pieceCoords.second;
        
        Piece* piece = board[(row*boardSize)+col].getPiece();
        int team = (piece->isControlled())? USER: OPPONENT;
        switch ( piece->getType()) {
                
            case CellTexture::PIECE_ROOK:{
                rookAreaOfEffect( row, col, team, board);
                break;
            }
                
            case CellTexture::PIECE_KNIGHT:{
                knightAreaOfEffect( row, col, team, board);
                break;
            }
                
            case CellTexture::PIECE_BISHOP:{
                bishopAreaOfEffect( row, col, team, board);
                break;
            }
                
            case CellTexture::PIECE_QUEEN:{
                rookAreaOfEffect( row, col,team, board);
                bishopAreaOfEffect( row, col, team, board);
                break;
            }
                
            case CellTexture::PIECE_KING:{
                break;
            }
                
            case CellTexture::PIECE_PAWN:{
                pawnAreaOfEffect(row, col, team);
                break;
            }
                
            default:
                break;
                
        }

    }
    
    for (int i=0; i<boardSize; i++) {
        std::cout << "+---+---+---+---+---+---+---+---+\n";
        for (int j=0; j<boardSize; j++) {
            std::cout << "| " << board_[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "+---+---+---+---+---+---+---+---+\n";
    
    
    
    return STATE_NOTHING;
}

void
BoardVerifier::pawnAreaOfEffect(int row, int col, int teamValue)
{
    if(teamValue==USER){
        if( (row-1)>0 && (col-1)>0)
            board_[row-1][col-1] = USER;
        if( (row-1)>0 && (col+1)>0)
            board_[row-1][col+1] = USER;
    }
    else{
        if( (row+1)>0 && (col-1)>0)
            board_[row+1][col-1] = OPPONENT;
        if( (row+1)>0 && (col+1)>0)
            board_[row+1][col-1] = OPPONENT;
    }
}

void
BoardVerifier::rookAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board )
{
    bool isBlocked= false; // Indicates if there is a piece blocking the way
    Piece* piece;
    
    // From coordinates to the right
    for(int i = col+1; i<boardSize && !isBlocked; i++){
        if( (piece=board[ (row*boardSize) +i].getPiece())==nullptr){
            board_[row][i]=teamValue;
        }
        else{
            if(piece && piece->isControlled())
                board_[row][i]=teamValue;

            isBlocked=true;
        }
    }
    
    // From position to the left
    isBlocked=false;
    piece=nullptr;
    for(int i = col-1; i>=0 && !isBlocked; i--){
        if( (piece=board[ (row*boardSize) +i].getPiece())==nullptr){
            board_[row][i]=teamValue;
        }
        else{
            if(piece && piece->isControlled())
                board_[row][i]=teamValue;
            isBlocked=true;
        }
    }
    
    // From position to the bottom
    isBlocked= false;
    piece=nullptr;
    for(int i = row+1; i<boardSize && !isBlocked; i++){
        if( (piece=board[ (i*boardSize) +col].getPiece())==nullptr){
            board_[i][col]=teamValue;
        }
        else{
            if(piece && piece->isControlled())
                board_[i][col]=teamValue;
            isBlocked=true;
        }
    }
    
    // From position to the top
    isBlocked= false;
    piece=nullptr;
    for(int i = row-1; i>=0 && !isBlocked; i--){
        if( (piece=board[ (i*boardSize) +col].getPiece())==nullptr){
            board_[i][col]=teamValue;
        }
        else{
            if(piece && piece->isControlled())
                board_[i][col]=teamValue;
            isBlocked=true;
        }
    }

}

void
BoardVerifier::knightAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board)
{
    const static int moveNo=8;
    int xValues[moveNo]={1,1,-1,-1,2,2,-2,-2};
    int yValues[moveNo]={2,-2,2,-2,1,-1,1,-1};
    
    for (int i=0; i<moveNo; i++) {
        int x = col + xValues[i];
        int y = row + yValues[i];
        if( y >= 0 && y < boardSize && x >= 0 && x < boardSize ){
            if( board[(boardSize*y) + x].getPiece() ){
                if( !board[(boardSize*y) + x].getPiece()->isControlled())
                    board_[y][x]=teamValue;
            }
            else
                board_[y][x]=teamValue;
        }
    }
}

void
BoardVerifier::bishopAreaOfEffect(int row, int col, int teamValue, std::vector<Cell> &board)
{
    std::bitset<4>validDirections( std::string("0000"));
    Piece* piece;
    
    for(int i= 1; validDirections.count()!=4; i++){
        if( !validDirections[0]){
            if(row+i >= boardSize || col+i >= boardSize)
                validDirections.flip(0);
            else if( (piece=board[(boardSize*(row+i)) + (col+i)].getPiece())==nullptr)
                board_[(row+i)][(col+i)]=teamValue;
            else{
                if(piece->isControlled())
                    board_[(row+i)][(col+i)]=teamValue;
                validDirections.flip(0);
            }
        }
        
        if(!validDirections[1]){
            if(row+i >= boardSize || col-i < 0)
                validDirections.flip(1);
            else if( (piece=board[(boardSize*(row+i)) + (col-i)].getPiece())==nullptr)
                board_[(row+i)][(col-i)]=teamValue;
            else{
                if(!piece->isControlled())
                    board_[(row+i)][(col-i)]=teamValue;
                validDirections.flip(1);
            }
        }
        
        if(!validDirections[2]){
            if(row-i < 0 || col+i >= boardSize)
                validDirections.flip(2);
            else if( (piece=board[(boardSize*(row-i)) + (col+i)].getPiece())==nullptr)
                board_[(row-i)][(col+i)]=teamValue;
            else{
                if(!piece->isControlled())
                    board_[(row-i)][(col+i)]=teamValue;
                validDirections.flip(2);
            }
        }
        
        if(!validDirections[3]){
            if( row-i < 0 || col-i < 0)
                validDirections.flip(3);
            else if( (piece=board[(boardSize*(row-i)) + (col-i)].getPiece())==nullptr)
                board_[(row-i)][(col-i)]=teamValue;
            else{
                if(!piece->isControlled())
                    board_[(row-i)][(col-i)]=teamValue;
                validDirections.flip(3);
            }
        }
    }
}

bool
BoardVerifier::verifyKingState(SDL_Point kingCoords)
{
    if( board_[kingCoords.x][kingCoords.y] == 2){
        state_ = STATE_CHECK;
        
        bool canMove = false;
        for(int i= kingCoords.x-1; i<= kingCoords.x+1; i++){
            for (int j = kingCoords.y-1; j<= kingCoords.y +1; j++) {
                if( i>=0 && i<boardSize && j>=0 && j<boardSize){
                    if(board_[i][j]==0)
                        canMove=true;
                }
            }
        }
        if (!canMove) {
            
            // Can anyone block?
            
            //if yes check and store blocker
            //if no, check_mate
        }
    }

    return true;
}

