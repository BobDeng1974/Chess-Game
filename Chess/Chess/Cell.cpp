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
    this->row_ = row;
    this->col_ = col;
    this->type_ = CellTexture::PIECE_EMPTY;
    this->isDark_ = isDark;
}

void Cell::render()
{
    SDL_Rect fillRect = { anchorPoint_.x, anchorPoint_.y, size_, size_ };
    
    ( isDark_)?
        SDL_SetRenderDrawColor( renderer_, 0xA5, 0x75, 0x51, 0xFF )  // Cell is dark ( cream)
        :SDL_SetRenderDrawColor( renderer_, 0xEB, 0xD1, 0xA6, 0xFF );   // Cell is light( light orange)
    SDL_RenderFillRect( renderer_, &fillRect );

    // Render piece if not empty
    if( type_ != CellTexture::PIECE_EMPTY)cellTexture_->render(anchorPoint_.x, anchorPoint_.y, type_);
    
}

void Cell::setType( CellTexture::Piece piecetype){ this->type_ = piecetype; }

void Cell::setClicable(bool clickable){ this->isClickable_ = clickable; }
