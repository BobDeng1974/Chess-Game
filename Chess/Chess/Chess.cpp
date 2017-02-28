//
//  Chess.cpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Chess.hpp"

Chess::Chess(SDL_Renderer* renderer, CellTexture* cellTexture, int screenWidth, int screenHeight)
{
    this->renderer_ = renderer;
    this->cellTexture_ = cellTexture;
    
    // TODO review sizing
    
    int smallerSize = (screenHeight<screenWidth)? screenHeight: screenWidth;
    
    cellSize_ = smallerSize/9;
    
    cellTexture_->setDimensions(cellSize_, cellSize_);
    
    boardHeight_ = (cellSize_*horizontalCellNo);
    boardWidth_ = boardHeight_;
    
    createBoard();
    initiatePieces();
}

// Creates the board
void Chess::createBoard()
{
    for (int i=0; i<horizontalCellNo; i++){
        for (int j=0; j<verticalCellNo; j++){
            bool isDark = ((i%2==0 && j%2==0)||((i%2==1 && j%2==1)))? false:true;
            board_.push_back( Cell(renderer_, cellTexture_, (cellSize_/2 + (j*cellSize_)), cellSize_/2 + (i*cellSize_) , cellSize_, i, j, isDark ));
        }
    }
}

void Chess::initiatePieces(){
    //Set Opponents Pieces
    for (int i=0; i<horizontalCellNo; i++){
        if(i == 0 || i== horizontalCellNo-1)
            board_[i].setType(CellTexture::PIECE_ROOK);
        else if( i==1 || i == horizontalCellNo-2)
            board_[i].setType(CellTexture::PIECE_KNIGHT);
        else if( i==2 || i== horizontalCellNo-3)
            board_[i].setType(CellTexture::PIECE_BISHOP);
        else if( i==3)
            board_[i].setType(CellTexture::PIECE_QUEEN);
        else
            board_[i].setType(CellTexture::PIECE_KING);
        
        board_[i].setClicable(false);
    }
    //Set Opponents pawns
    for (int i=0; i<horizontalCellNo; i++){
        board_[horizontalCellNo + i].setType(CellTexture::PIECE_PAWN);
        board_[horizontalCellNo + i].setClicable(false);
    }
    
    // Set players pieces
    int row = ((verticalCellNo-1)*horizontalCellNo);
    for (int i=0; i<horizontalCellNo; i++){
        if(i == 0 || i== horizontalCellNo-1)
            board_[row + i].setType(CellTexture::PIECE_ROOK);
        else if( i==1 || i == horizontalCellNo-2)
            board_[row + i].setType(CellTexture::PIECE_KNIGHT);
        else if( i==2 || i== horizontalCellNo-3)
            board_[row + i].setType(CellTexture::PIECE_BISHOP);
        else if( i==3)
            board_[row + i].setType(CellTexture::PIECE_QUEEN);
        else
            board_[row + i].setType(CellTexture::PIECE_KING);
        
        board_[row + i].setClicable(true);
    }
    row+=horizontalCellNo;
    //Set Players pawns
    for (int i=0; i<horizontalCellNo; i++){
        board_[row + i].setType(CellTexture::PIECE_PAWN);
        board_[row + i].setClicable(true);
    }
}

// Renders the board
void Chess::render()
{
    // Render each cell
    for (int i=0; i<horizontalCellNo; i++){
        for (int j=0; j<verticalCellNo; j++){
            board_[(i*horizontalCellNo) + j].render();
        }
    }
    
    
    SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xFF );
    
    //Render black outlined quad
    SDL_Rect outlineRect = { cellSize_/2, cellSize_/2, boardWidth_, boardHeight_ };
    SDL_RenderDrawRect( renderer_, &outlineRect );
 
}
