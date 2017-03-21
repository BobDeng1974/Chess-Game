//
//  boardVerifier.cpp
//  Chess
//
//  Created by Ricardo Martins on 05/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "BoardVerifier.hpp"

BoardVerifier::BoardVerifier()
{
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            board_.push_back( CellVerifier(i, j));
        }
    }

}

BoardVerifier::State
BoardVerifier::verifyBoardState(std::vector<Cell> &board, int turn)
{
    currentTurn = turn;
    
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            int index =(i*boardSize)+j;
            Piece* piece;
            board_[index].reset();
            if( (piece=board[index].getPiece())!=nullptr){
                board_[index].setPiece(piece);
                if( board_[index].getOwner()==USER){
                    if(piece->getType() ==CellTexture::PIECE_KING){
                        kingIndex_ = index;
                        king_ = piece;
                    }
                    else{
                        piecesUserQueue_.push(index);
                        piecesQueue_.push(index);
                    }
                }
                else
                    piecesQueue_.push(index);
            }
        }
    }

    while (!piecesQueue_.empty()) {
        int pieceIndex = piecesQueue_.front();
        piecesQueue_.pop();
        
        int row = pieceIndex/boardSize;
        int col = pieceIndex%boardSize;
        switch ( board_[pieceIndex].getPiece()->getType()) {
            case CellTexture::PIECE_ROOK:{
                rookAreaOfEffect( row, col);
                break;
            }
                
            case CellTexture::PIECE_KNIGHT:{
                knightAreaOfEffect( row, col);
                break;
            }
                
            case CellTexture::PIECE_BISHOP:{
                bishopAreaOfEffect( row, col);
                break;
            }
                
            case CellTexture::PIECE_QUEEN:{
                rookAreaOfEffect( row, col);
                bishopAreaOfEffect( row, col);
                break;
            }
                
            case CellTexture::PIECE_KING:{
                kingAreaOfEffect(row, col);
                break;
            }
                
            case CellTexture::PIECE_PAWN:{
                pawnAreaOfEffect(row, col);
                break;
            }
                
            default:
                break;
                
        }

    }
    
    while (!kingBlockers_.empty()) {
        int pos = kingBlockers_.front();
        kingBlockers_.pop();
        board_[pos].pruneProtectKingMovement();
    }
    
    verifyKingState();
    
    for (int i=0; i<boardSize; i++) {
        std::cout << "+---+---+---+---+---+---+---+---+\n";
        for (int j=0; j<boardSize; j++) {
            std::cout << "| " << ((board_[i*boardSize + j].isReachable())?2:0) << " " ;
            
        }
        std::cout << "|\n";
    }
    std::cout << "+---+---+---+---+---+---+---+---+\n\n\n";
    
    for (int i=0; i<boardSize; i++) {
        std::cout << "+---+---+---+---+---+---+---+---+\n";
        for (int j=0; j<boardSize; j++) {
            std::cout << "| ";
            if(board_[i*boardSize + j].isProtectingKing())
                std::cout << 3 << " ";
            else if( board_[i*boardSize + j].getOwner() == OPPONENT )
                std::cout << 2 << " ";
            else if( board_[i*boardSize + j].getOwner() == USER)
                std::cout << 1 << " ";
            else
                std::cout << 0 << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "+---+---+---+---+---+---+---+---+\n";
    return state_;
}

std::queue<int>
BoardVerifier::getPieceMoves(int index){ return board_[index].getMoves(); }
bool
BoardVerifier::isCastleMove(int index) const { return board_[index].isCastleMove();}

// Private Functions
void
BoardVerifier::pawnAreaOfEffect(int row, int col)
{
    Piece* piece;
    if(board_[row*boardSize + col].getOwner()==USER){
        int piecePos =(row)*boardSize  + col;
        int index = (row-1)*boardSize  + col;
        if( row-1 > 0){
            
            if( (col-1)>0 && board_[index-1].getOwner()==OPPONENT) // eat to the left
                board_[piecePos].setMove(index-1);
            if( (col+1)<boardSize && board_[index+1].getOwner()==OPPONENT) // eat to the right
                board_[piecePos].setMove(index+1);
            if( board_[index].getOwner()==0){ // move forward
                board_[piecePos].setMove(index);
                if (!board_[piecePos].getPiece()->hasMoved() && board_[index - boardSize].getOwner()==0) // If forward is empty, verify if double if possible
                    board_[piecePos].setMove(index-boardSize);
            }
            if( (col-1)>0 && board_[index-1 + boardSize].getOwner()==OPPONENT && board_[index-1 + boardSize].getPassant(currentTurn)) // Passant to the left
                board_[piecePos].setMove(index-1);
            if( (col+1)>0 && board_[index+1 + boardSize].getOwner()==OPPONENT && board_[index+1 + boardSize].getPassant(currentTurn)) // Passant to the right
                board_[piecePos].setMove(index+1);
        }
    }
    else{
        if( (row+1)<boardSize && (col-1)>0){
            board_[(row+1)*boardSize  + (col-1)].setReachable();
            if( (piece = board_[(row+1)*boardSize  + (col-1)].getPiece())!=nullptr)
                if( piece->getType() == CellTexture::PIECE_KING && board_[(row+1)*boardSize  + (col-1)].getOwner()==USER)
                    kingThreats_.push( row*boardSize + col ); // has direct LoS to king
        }
        if( (row+1)<boardSize && (col+1)<boardSize){
            board_[(row+1)*boardSize  + (col+1)].setReachable();
            if( (piece = board_[(row+1)*boardSize  + (col+1)].getPiece())!=nullptr)
                if( piece->getType() == CellTexture::PIECE_KING && board_[(row+1)*boardSize  + (col+1)].getOwner()==USER)
                    kingThreats_.push( row*boardSize + col ); // has direct LoS to king
        }
    }
}

void
BoardVerifier::rookAreaOfEffect(int row, int col)
{
    int blockingPieces= 0; // Indicates if there is a piece blocking the way
    Piece* piece;
    int hitCell=0;
    bool isUserPiece = board_[row*boardSize + col].getPiece()->isControlled();
    // From coordinates to the right
    for(int i = col+1; i<boardSize && blockingPieces<2; i++){
        int index = (row*boardSize) +i;
        if( (piece=board_[ index].getPiece())==nullptr){
            if( isUserPiece) // Is Owned
                board_[row*boardSize +col].setMove(index);
            else if(blockingPieces==0) // hasnt met a piece in the way, set as reachable
                board_[index].setReachable();
        }
        else{
            if( piece->isControlled() && !isUserPiece){ // Enemy found user piece
                if( blockingPieces==0) // hasnt met a piece in the way, set as reachable
                    board_[index].setReachable();
                if( index == kingIndex_){ // Found king
                    if(blockingPieces==1){ // has already found a piece, block it so it can't move
                        board_[hitCell].setProtectsKing(CellVerifier::DIR_O);
                        kingBlockers_.push(hitCell);
                    }
                    else{
                        kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                        board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_E);
                    }
                    blockingPieces=2;
                }
                else{ // Found something else, mark the positions
                    hitCell = index;
                    blockingPieces++;
                }
            }
            else{ // Found another enemy piece, stop looking
                if( isUserPiece && !piece->isControlled())
                    board_[row*boardSize +col].setMove(index);
                else
                    board_[index].setReachable();
                blockingPieces=2;
            }
        }
    }
    
    // From position to the left
    blockingPieces=0;
    piece=nullptr;
    for(int i = col-1; i>=0 && blockingPieces<2; i--){
        int index = (row*boardSize) +i;
        if( (piece=board_[ (row*boardSize) +i].getPiece())==nullptr){
            if( isUserPiece) // Is Owned
                board_[row*boardSize +col].setMove(index);
            else if(blockingPieces==0) // hasnt met a piece in the way, set as reachable
                board_[row*boardSize + i].setReachable();
        }
        else{
            if( piece->isControlled() && !isUserPiece){
                if( blockingPieces==0) // Found edible piece, set as reachable
                    board_[row*boardSize + i].setReachable();
                if( row*boardSize + i == kingIndex_){ // Found king
                    if(blockingPieces==1){ // has already found a piece, block it so it can't move
                        board_[hitCell].setProtectsKing(CellVerifier::DIR_E);
                        kingBlockers_.push(hitCell);
                    }
                    else{
                        kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                        board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_E);
                    }
                    blockingPieces=2;
                }
                else{ // Found something else, mark the positions
                    hitCell = row*boardSize + i;
                    blockingPieces++;
                }
            }
            else{ // Found another enemy piece, stop looking
                if( isUserPiece && !piece->isControlled())
                    board_[row*boardSize +col].setMove(index);
                else
                    board_[index].setReachable();
                blockingPieces=2;
            }
        }
    }

    // From position to the bottom
    blockingPieces= 0;
    piece=nullptr;
    for(int i = row+1; i<boardSize && blockingPieces<2; i++){
        int index = i*boardSize + col;
        if( (piece=board_[ index].getPiece())==nullptr){
            if( isUserPiece) // Is Owned
                board_[row*boardSize +col].setMove(index);
            else  if(blockingPieces==0) // hasnt met a piece in the way, set as reachable
                board_[index].setReachable();
        }
        else{
            if(piece && piece->isControlled()&& !isUserPiece){
                if( blockingPieces==0) // Found edible piece, set as reachable
                    board_[i*boardSize + col].setReachable();
                if( i*boardSize + col == kingIndex_){// Found king
                    if(blockingPieces==1){ // has already found a piece, block it so it can't move
                        board_[hitCell].setProtectsKing(CellVerifier::DIR_N);
                        kingBlockers_.push(hitCell);
                    }
                    else{
                        kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                        board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_N);
                    }
                    blockingPieces=2;
                }
                else{ // Found something else, mark the positions
                    hitCell = i*boardSize + col;
                    blockingPieces++;
                }
            }
            else{ // Found another enemy piece, stop looking
                if( isUserPiece && !piece->isControlled())
                    board_[row*boardSize +col].setMove(index);
                else
                    board_[index].setReachable();
                blockingPieces=2;
            }
        }
    }
    
    // From position to the top
    blockingPieces= 0;
    piece=nullptr;
    for(int i = row-1; i>=0 && blockingPieces<2; i--){
        int index = i*boardSize + col;
        if( (piece=board_[ (i*boardSize) +col].getPiece())==nullptr){
            if( isUserPiece) // Is Owned
                board_[row*boardSize +col].setMove(index);
            else if(blockingPieces==0) // hasnt met a piece in the way, set as reachable
                board_[i*boardSize + col].setReachable();
        }
        else{
            if(piece && piece->isControlled()&& !isUserPiece){
                if( blockingPieces==0) // Found edible piece, set as reachable
                    board_[i*boardSize + col].setReachable();
                if( i*boardSize + col == kingIndex_){// Found king
                    if(blockingPieces==1){ // has already found a piece, block it so it can't move
                        board_[hitCell].setProtectsKing(CellVerifier::DIR_S);
                        kingBlockers_.push(hitCell);
                    }
                    else{
                        kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                        board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_N);
                    }
                    blockingPieces=2;
                }
                else{ // Found something else, mark the positions
                    hitCell = i*boardSize + col;
                    blockingPieces++;
                }
            }
            else{ // Found another enemy piece, stop looking
                if( isUserPiece && !piece->isControlled())
                    board_[row*boardSize +col].setMove(index);
                else
                    board_[index].setReachable();
                blockingPieces=2;
            }
        }
    }
}

void
BoardVerifier::knightAreaOfEffect(int row, int col)
{
    const static int moveNo=8;
    int xValues[moveNo]={1,1,-1,-1,2,2,-2,-2};
    int yValues[moveNo]={2,-2,2,-2,1,-1,1,-1};
 
    bool isUserPiece = board_[row*boardSize + col].getPiece()->isControlled();
    Piece* piece;
    for (int i=0; i<moveNo; i++) {
        int x = col + xValues[i];
        int y = row + yValues[i];
        int index = y*boardSize + x;
        if( y >= 0 && y < boardSize && x >= 0 && x < boardSize ){
            if( (piece=board_[index].getPiece()) ){
                if(!isUserPiece){ // Enemy piece, always as reachable (indicates different depending on piece)
                    board_[index].setReachable();
                    if( piece->isControlled() && piece->getType() == CellTexture::PIECE_KING) // User king is vulnerable
                        kingThreats_.push( row*boardSize + col );
                }
                else if( !piece->isControlled() && isUserPiece) // User piece, found enemy piece
                    board_[row*boardSize + col].setMove(index);
            }
            else{ // Empty cell, set as reachable
                if( isUserPiece)
                    board_[row*boardSize + col].setMove(index);
                else
                    board_[index].setReachable();
            }
        }
    }
}

void
BoardVerifier::bishopAreaOfEffect(int row, int col)
{
    std::bitset<4>validDirections( std::string("0000"));
    Piece* piece;
    bool isUserPiece = board_[row*boardSize + col].getPiece()->isControlled();
    int obstaclesFound[4]={0,0,0,0};
    int obstaclesIndex[4]={0,0,0,0};
    for(int i= 1; validDirections.count()!=4; i++){
        if( !validDirections[0]){ // SE direction
            if(row+i >= boardSize || col+i >= boardSize) // If outside board, flip == dont check anymore
                validDirections.set(0);
            else if( (piece=board_[(boardSize*(row+i)) + (col+i)].getPiece())==nullptr){ // Found empty space
                if(isUserPiece) //if user piece we set as possible valid move
                    board_[row*boardSize + col].setMove((row+i)*boardSize + (col+i));
                else if( obstaclesFound[0]==0) // else if we set as reachable
                    board_[(row+i)*boardSize + (col+i)].setReachable();
            }
            else{
                if(!isUserPiece){ //  enemy piece
                    if( piece->isControlled() && (row+i)*boardSize + (col+i) == kingIndex_){ // if found user king
                        if(obstaclesFound[0]==1){ // had already found a piece, block it
                            board_[obstaclesIndex[0]].setProtectsKing(CellVerifier::DIR_NO);
                            kingBlockers_.push(obstaclesIndex[0]);
                        }
                        else{
                            kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                            board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_SE);
                        }
                        validDirections.set(0);
                    }
                    if(obstaclesFound[0]==0){ // if first obtacle found, set it as edible
                        board_[(row+i)*boardSize + (col+i)].setReachable();
                        if(!piece->isControlled()) // is found enemypiece, path blocked, stop
                            validDirections.set(0);
                        else{ // Else stro the piece, incase it is protecting the king
                            obstaclesIndex[0] = (row+i)*boardSize + (col+i);
                            obstaclesFound[0]++;
                        }
                    }else
                        validDirections.set(0); // Found second blocking piece, finish search here
                }
                else{ // User piece
                    if( !piece->isControlled() && isUserPiece){ // If user piece found an enemy one
                        board_[row*boardSize + col].setMove((row+i)*boardSize + (col+i));
                        validDirections.set(0);
                    }
                    else
                        validDirections.set(0);
                }
            }
        }
        
        if( !validDirections[1]){ // SO direction
            if(row+i >= boardSize ||  col-i < 0) // If outside board, flip == dont check anymore
                validDirections.set(1);
            else if( (piece=board_[(boardSize*(row+i)) + (col-i)].getPiece())==nullptr){ // Found empty space
                if(isUserPiece) //if user piece we set as possible valid move
                    board_[row*boardSize + col].setMove((row+i)*boardSize + (col-i));
                else if( obstaclesFound[1]==0) // else if we set as reachable
                    board_[(row+i)*boardSize + (col-i)].setReachable();
            }
            else{
                if( !isUserPiece){ // if enemy found one of users pieces
                    if( piece->isControlled() && (row+i)*boardSize + (col-i) == kingIndex_){ // if found king
                        if(obstaclesFound[1]==1){ // had already found a piece, block it
                            board_[obstaclesIndex[1]].setProtectsKing(CellVerifier::DIR_NE);
                            kingBlockers_.push(obstaclesIndex[1]);
                        }
                        else{
                            kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                            board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_SO);
                        }
                        validDirections.set(1);
                    }
                    if(obstaclesFound[1]==0){ // if first obtacle found, set it as edible
                        board_[(row+i)*boardSize + (col-i)].setReachable();
                        if(!piece->isControlled()) // is found enemypiece, path blocked, stop
                            validDirections.set(1);
                        else{
                            obstaclesIndex[1] = (row+i)*boardSize + (col-i);
                            obstaclesFound[1]++;
                        }
                    }else
                        validDirections.set(1); // Found second blocking piece, finish search here
                }
                else{
                    if( !piece->isControlled() && isUserPiece){ // If user piece found an enemy one
                        board_[row*boardSize + col].setMove((row+i)*boardSize + (col-i));
                        validDirections.set(1);
                    }
                    else
                        validDirections.set(1);
                }
            }
        }
        
        if( !validDirections[2]){ // NE direction
            if(row-i < 0 || col+i >= boardSize) // If outside board, flip == dont check anymore
                validDirections.set(2);
            else if( (piece=board_[(boardSize*(row-i)) + (col+i)].getPiece())==nullptr){ // Found empty space
                if(isUserPiece) //if user piece we set as possible valid move
                    board_[row*boardSize + col].setMove((row-i)*boardSize + (col+i));
                else if( obstaclesFound[2]==0) // else if we set as reachable
                    board_[(row-i)*boardSize + (col+i)].setReachable();
            }
            else{
                if( !isUserPiece){ // if enemy found one of users pieces
                    if(piece->isControlled() && (row-i)*boardSize + (col+i) == kingIndex_){ // if found king
                        if(obstaclesFound[2]==1){ // had already found a piece, block it
                            board_[obstaclesIndex[2]].setProtectsKing(CellVerifier::DIR_SO);
                            kingBlockers_.push(obstaclesIndex[2]);
                        }
                        else{
                            kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                            board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_NE);
                        }
                        validDirections.set(2);
                    }
                    if(obstaclesFound[2]==0){ // if first obtacle found, set it as edible
                        board_[(row-i)*boardSize + (col+i)].setReachable();
                        if(!piece->isControlled()) // is found enemypiece, path blocked, stop
                            validDirections.set(2);
                        else{
                            obstaclesIndex[2] = (row-i)*boardSize + (col+i);
                            obstaclesFound[2]++;
                        }
                    }else
                        validDirections.set(2); // Found second blocking piece, finish search here
                }
                else{
                    if( !piece->isControlled() && isUserPiece){ // If user piece found an enemy one
                        board_[row*boardSize + col].setMove((row-i)*boardSize + (col+i));
                        validDirections.set(2);
                    }
                    else
                        validDirections.set(2);
                }
            }
        }
        
        if( !validDirections[3]){ // NO direction
            if( row-i < 0 || col-i < 0) // If outside board, flip == dont check anymore
                validDirections.set(3);
            else if( (piece=board_[(boardSize*(row-i)) + (col-i)].getPiece())==nullptr){ // Found empty space
                if(isUserPiece) //if user piece we set as possible valid move
                    board_[row*boardSize + col].setMove((row-i)*boardSize + (col-i));
                else if( obstaclesFound[3]==0) // else if we set as reachable
                    board_[(row-i)*boardSize + (col-i)].setReachable();
            }
            else{
                if(piece->isControlled() && !isUserPiece){ // if enemy found one of users pieces
                    if(piece->isControlled() && (row-i)*boardSize + (col-i) == kingIndex_){ // if found king
                        if(obstaclesFound[3]==1){ // had already found a piece, block it
                            board_[obstaclesIndex[3]].setProtectsKing(CellVerifier::DIR_NO);
                            kingBlockers_.push(obstaclesIndex[3]);
                        }
                        else{
                            kingThreats_.push( row*boardSize + col ); // has direct LoS to king
                            board_[kingIndex_].setAttackerDirection(CellVerifier::DIR_NO);
                        }
                        validDirections.set(3);
                    }
                    if(obstaclesFound[3]==0){ // if first obtacle found, set it as edible
                        board_[(row-i)*boardSize + (col-i)].setReachable();
                        if(!piece->isControlled()) // is found enemypiece, path blocked, stop
                            validDirections.set(3);
                        else{
                            obstaclesIndex[3] = (row-i)*boardSize + (col-i);
                            obstaclesFound[3]++;
                        }
                    }else
                        validDirections.set(3); // Found second blocking piece, finish search here
                }
                else{
                    if( !piece->isControlled() && isUserPiece){ // If user piece found an enemy one
                        board_[row*boardSize + col].setMove((row-i)*boardSize + (col-i));
                        validDirections.set(3);
                    }
                    else
                        validDirections.set(3);
                }
            }
        }
    }
}

void
BoardVerifier::kingAreaOfEffect(int row, int col)
{
    Piece* piece;
    int ymin = ( row-1 >= 0)? row-1:row;
    int ymax = ( row+1 < boardSize)? row+1:row;
    int xmin = ( col-1 >= 0)? col-1:col;
    int xmax = ( col+1 < boardSize)? col+1:col;
    bool isUserPiece = board_[row*boardSize + col].getPiece()->isControlled();
    for(int x = xmin; x <= xmax; x++ ){
        for( int y = ymin; y <= ymax; y++){
            int index = y*boardSize + x;
            if( (x!=col || y!=row)){
                if((piece = board_[index].getPiece())==nullptr){ // space is empty
                    if (isUserPiece && !board_[index].isReachable()){ // User king moving onto empty space that isn't reachable by enemy
                        if( x == col && !board_[row*boardSize + col].isAttackedFromDirection(CellVerifier::DIR_N))
                            board_[row*boardSize + col].setMove(index);
                        else if( y == row && !board_[row*boardSize + col].isAttackedFromDirection(CellVerifier::DIR_E))
                            board_[row*boardSize + col].setMove(index);
                        else if( ((y - row)/( x - col))<0 && !board_[row*boardSize + col].isAttackedFromDirection(CellVerifier::DIR_NE))
                            board_[row*boardSize + col].setMove(index);
                        else if( ((y - row)/( x - col))>0 && !board_[row*boardSize + col].isAttackedFromDirection(CellVerifier::DIR_SE))
                            board_[row*boardSize + col].setMove(index);
                    }
                    else if( !isUserPiece) // if enemy king, just set space as reachable
                        board_[index].setReachable();
                }else{
                    if(isUserPiece && !piece->isControlled() && !board_[index].isReachable()) // user king, onto enemy piece that isn't protected
                        board_[row*boardSize + col].setMove(index);
                    else if( !isUserPiece) // enemy king onto piece
                        board_[index].setReachable();
                }
            }
        }
    }
    if( isUserPiece && !board_[kingIndex_].getPiece()->hasMoved())
        verifyCastle();
}

void
BoardVerifier::verifyCastle()
{
    bool isValidMove=true;
    if( board_[(boardSize-1)*boardSize].getPiece()!=nullptr && !board_[(boardSize-1)*boardSize].getPiece()->hasMoved() ){
        // Left Rook hasn't moved
        for(int x=1; x<3; x++){
            if(board_[(boardSize-1)*boardSize + x].getPiece()==nullptr && board_[(boardSize-1)*boardSize + x].isReachable())
                isValidMove = false;
        }
        if( isValidMove){
            board_[kingIndex_].setMove((boardSize-1)*boardSize + 2); // Set move for castle
            board_[(boardSize-1)*boardSize + 2].setCastleMove();
        }
    }
    
    if( board_[boardSize*boardSize -1].getPiece()!=nullptr && !board_[boardSize*boardSize-1].getPiece()->hasMoved() ){
        // Right Rook hasn't moved
        for(int x=5; x<7; x++){
            if( board_[(boardSize-1)*boardSize + x].getPiece()==nullptr && board_[(boardSize-1)*boardSize + x].isReachable())
                isValidMove = false;
        }
        if( isValidMove){
            board_[kingIndex_].setMove((boardSize-1)*boardSize + 6); // Set move for castle
            board_[(boardSize-1)*boardSize + 6].setCastleMove();
        }
    }

}

bool
BoardVerifier::verifyKingState()
{
    state_ = STATE_NOTHING;
    
    kingAreaOfEffect(kingIndex_/boardSize, kingIndex_%boardSize);

    
    if( board_[kingIndex_].isReachable()){
        if( board_[kingIndex_].isMovable()){
            state_ = STATE_CHECK;
            if( kingThreats_.size()>1)
                onlyKingMoves = true;
            else
                UpdateUserPieceMoves(); // Update move possibilities
        }
        else{
            if( kingThreats_.size()>1)
                state_ = STATE_CHECKMATE;
            else{
                state_ = STATE_CHECK;
                if (!UpdateUserPieceMoves()) {
                    state_ = STATE_CHECKMATE;
                }
            }
        }
    }
    else if( !board_[kingIndex_].isMovable()){
        if( !UpdateUserPieceMoves())
            state_ = STATE_STALEMATE;
    }
    
    return (state_ == STATE_CHECKMATE);
}

bool
BoardVerifier::UpdateUserPieceMoves()
{
    if( kingThreats_.empty())
        return true;
    int attacker = kingThreats_.front();
    kingThreats_.pop();
    std::vector<int> possibleCells;
    switch (board_[attacker].getPiece()->getType() ) {
        case CellTexture::PIECE_PAWN:
            possibleCells.push_back(attacker);
            break;
       
        case CellTexture::PIECE_KNIGHT:
            possibleCells.push_back(attacker);
            break;
            
        case CellTexture::PIECE_ROOK:{
            int min, max;
            if( attacker/8 == kingIndex_/8){ // they are in the same row
                if( attacker%8 < kingIndex_%8){
                    min = attacker%8;
                    max = kingIndex_%8;
                }
                else{
                    min = kingIndex_%8;
                    max = attacker%8;
                }
                for(int i = min ; i<=max; i++){
                    if( (kingIndex_/8)*boardSize + i != kingIndex_)
                        possibleCells.push_back((kingIndex_/8)*boardSize + i);
                }
            }
            else{ // They are in the same column
                if( attacker/8 < kingIndex_/8){
                    min = attacker/8;
                    max = kingIndex_/8;
                }
                else{
                    min = kingIndex_/8;
                    max = attacker/8;
                }
                for(int i = min ; i<=max; i++){
                    if( i*boardSize + kingIndex_%8 != kingIndex_)
                        possibleCells.push_back(i*boardSize + kingIndex_%8);
                }
            }
            break;
        }
        case CellTexture::PIECE_BISHOP:{
            int row, col, length;
            if( attacker%8 < kingIndex_%8){
                row = attacker/8;
                col = attacker%8;
                length = (kingIndex_%8 - attacker%8);
            }
            else{
                row = kingIndex_/8;
                col = kingIndex_%8;
                length = (attacker%8 - kingIndex_%8);
            }
            if( ((attacker/8 - kingIndex_/8)/( attacker%8 - kingIndex_%8))<0 ){  // direction SO - NE  /
                for(int i = 0 ; i<length; i++){
                    if( (row-i)*boardSize + (col+i) != kingIndex_)
                        possibleCells.push_back((row-i)*boardSize + (col+i));
                }
            }
            else{ // direction NO - SE
                for(int i = 0 ; i<length; i++){
                    if( (row+i)*boardSize + (col+i) != kingIndex_)
                        possibleCells.push_back((row+i)*boardSize + (col+i));
                }
            }
            break;
        }
            
        case CellTexture::PIECE_QUEEN:{
            int min, max,row, col, length;
            if( attacker/8 == kingIndex_/8){ // they are in the same row
                if( attacker%8 < kingIndex_%8){
                    min = attacker%8;
                    max = kingIndex_%8;
                }
                else{
                    min = kingIndex_%8;
                    max = attacker%8;
                }
                for(int i = min ; i<=max; i++){
                    if( (kingIndex_/8)*boardSize + i != kingIndex_)
                        possibleCells.push_back((kingIndex_/8)*boardSize + i);
                }
            }
            else if (attacker%8 == kingIndex_%8){ // They are in the same column
                if( attacker/8 < kingIndex_/8){
                    min = attacker/8;
                    max = kingIndex_/8;
                }
                else{
                    min = kingIndex_/8;
                    max = attacker/8;
                }
                for(int i = min ; i<=max; i++){
                    if( i*boardSize + kingIndex_%8 != kingIndex_)
                        possibleCells.push_back(i*boardSize + kingIndex_%8);
                }
            }
            else{
                if( attacker%8 < kingIndex_%8){
                    row = attacker/8;
                    col = attacker%8;
                    length = (kingIndex_%8 - attacker%8);
                }
                else{
                    row = kingIndex_/8;
                    col = kingIndex_%8;
                    length = (attacker%8 - kingIndex_%8);
                }
                if( ((attacker/8 - kingIndex_/8)/( attacker%8 - kingIndex_%8))<0 ){  // direction SO - NE  /
                    for(int i = 0 ; i<length; i++){
                        if( (row-i)*boardSize + (col+i) != kingIndex_)
                            possibleCells.push_back((row-i)*boardSize + (col+i));
                    }
                }
                else{ // direction NO - SE
                    for(int i = 0 ; i<length; i++){
                        if( (row+i)*boardSize + (col+i) != kingIndex_)
                            possibleCells.push_back((row+i)*boardSize + (col+i));
                    }
                }
            }
        }
    }
    bool validMoves=false;
    while( !piecesUserQueue_.empty()){
        int index = piecesUserQueue_.front();
        piecesUserQueue_.pop();
        if(board_[index].pruneMovements( possibleCells))
            validMoves=true;
    }
    
    return validMoves;
}


