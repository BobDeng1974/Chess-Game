//
//  Cell.cpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Cell.hpp"

Cell::Cell(SDL_Renderer* renderer, CellTexture* cellTexture, int x, int y, int size, int row, int col, bool isDark)
{
    this->renderer_ = renderer;
    this->cellTexture_ = cellTexture;
    this->anchorPoint_.x = x;
    this->anchorPoint_.y = y;
    this->size_ = size;
    this->boardPosition_.y = row;
    this->boardPosition_.x = col;
    this->isDark_ = isDark;
    reset();
}

void Cell::render()
{
    SDL_Rect fillRect = { anchorPoint_.x, anchorPoint_.y, size_, size_ };
    
    ( isDark_)?
        SDL_SetRenderDrawColor( renderer_, 0xA5, 0x75, 0x51, 0xFF )  // Cell is dark ( cream)
        :SDL_SetRenderDrawColor( renderer_, 0xEB, 0xD1, 0xA6, 0xFF );   // Cell is light( light orange)
    SDL_RenderFillRect( renderer_, &fillRect );

    if(isLegal_) cellTexture_->render(anchorPoint_.x, anchorPoint_.y, CellTexture::PIECE_LEGALMOVE );
    
    // Render piece if not empty
    if( piece_!=nullptr) cellTexture_->render(anchorPoint_.x, anchorPoint_.y, piece_->getType() );
}

bool Cell::handleEvent(SDL_Event *e)
{
    if( piece_ == nullptr && e->type == SDL_MOUSEBUTTONDOWN ) return false;
    //if( !isLegal_ && e->type == SDL_MOUSEBUTTONUP ) return false;

    //Get mouse position
    int x, y;
    SDL_GetMouseState( &x, &y );
    
    //Check if mouse is in button
    bool inside = true;
    
    //Mouse is left of the button
    if( x < anchorPoint_.x )
    {
        inside = false;
    }
    //Mouse is right of the button
    else if( x > anchorPoint_.x + size_ )
    {
        inside = false;
    }
    //Mouse above the button
    else if( y < anchorPoint_.y )
    {
        inside = false;
    }
    //Mouse below the button
    else if( y > anchorPoint_.y + size_ )
    {
        inside = false;
    }
    return inside;
}

void Cell::reset()
{
    if( this->piece_ != nullptr){
        delete piece_;
        this->piece_ = nullptr;
    }
    this->isLegal_ = false;
    this->isClicked_ = false;
}

void Cell::deletePiece()
{
    if( piece_!= nullptr){
        delete piece_;
        piece_=nullptr;
    }
}

void Cell::setPiece(Piece* piece) { this->piece_ = piece; }
void Cell::setClicked(bool clicked){ this->isClicked_ = clicked; }
void Cell::setLegalMove(bool isLegal){ this->isLegal_ = isLegal; }

Piece* Cell::getPiece() const { return piece_; }
bool Cell::isLegalMove() const { return isLegal_; }
SDL_Point Cell::getPosition() const { return boardPosition_; }

