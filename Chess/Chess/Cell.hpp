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

#include "Piece.hpp"
#include "CellTexture.hpp"

class Cell
{
public:
    Cell(SDL_Renderer* renderer, CellTexture* cellTexture,  int x, int y, int size, int row, int col, bool isDark);
    
    // Render Cell
    void render();
    
    //handle input (mouse clicks)
    bool handleEvent(SDL_Event* e);
    
    // Reset initial state
    virtual void reset();

    // Deletes its associated Piece
    void deletePiece();
    
    // Sets the type of the
    void setPiece( Piece* piece);
    void setClicked( bool clicked);
    void setLegalMove(bool isLegal);

    //Getters
    Piece* getPiece() const;
    bool isLegalMove() const;
    SDL_Point getPosition() const;

private:
    // SDL Variables
    SDL_Renderer* renderer_ =nullptr;
    CellTexture* cellTexture_ =nullptr;
    
    // GUI position and size
    SDL_Point anchorPoint_;
    int size_;
    
    // Board coordinates of the cell
    SDL_Point boardPosition_;
    
    // Indicates what the call contains
    Piece* piece_ = nullptr; // if it has a piece
    bool isDark_;       // if it is dark or light colored
    bool isClicked_;  // if it belongs to user or opponent
    bool isLegal_;      // if cell is a legal move
};
#endif /* Cell_hpp */
