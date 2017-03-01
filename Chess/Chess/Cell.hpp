//
//  Cell.hpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>

#include "CellTexture.hpp"

class Cell
{
public:
    Cell(SDL_Renderer* renderer, CellTexture* cellTexture,  int x, int y, int size, int row, int col, bool isDark);
    
    // Render Cell
    void render();
    
    //handle input (mouse clicks)
    bool handleEvent(SDL_Event* e);
    
    // Sets the type of the 
    void setType( CellTexture::Piece piecetype);
    void setClicable( bool clickable);
    
    //Getters
    CellTexture::Piece getType() const;

private:
    // SDL Variables
    SDL_Renderer* renderer_ =nullptr;
    CellTexture* cellTexture_ =nullptr;
    
    // GUI position and size
    SDL_Point anchorPoint_;
    int size_;
    
    // Board coordinates of the cell
    int row_;
    int col_;
    
    // Indicates what the call contains
    CellTexture::Piece type_; // if it has a piece
    bool isDark_; // if it is dark or light colored
    bool isClickable_; // if it belongs to user or opponent
};
#endif /* Cell_hpp */
