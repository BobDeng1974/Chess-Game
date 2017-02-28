//
//  Texture.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 17/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>
#include <string>

class CellTexture
{
public:
    enum Piece{PIECE_KING, PIECE_PAWN, PIECE_ROOK, PIECE_QUEEN, PIECE_KNIGHT, PIECE_BISHOP, PIECE_LEGALMOVE, PIECE_EMPTY};
    
    //Initializes variables
    CellTexture( SDL_Renderer* renderer, int cellWidth, int cellHeight);
    
    //Deallocates memory
    ~CellTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path , bool hasColorkey=false, uint8_t red = 0xFF, uint8_t green = 0xFF, uint8_t blue = 0xFF);
    
    //Renders texture at given point
    void render( int x, int y, CellTexture::Piece pieceType);
    
    
    // Set Texture Properties
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    // set render dimensions
    void setDimensions( int width, int height);
    
    //Deallocates texture
    void free();

private:
    //The actual hardware texture
    SDL_Texture* mTexture_;
    
    SDL_Renderer* renderer_=nullptr;

    const static int imageNo_ = 7;
    SDL_Rect gSpriteClips[imageNo_];
    
    //cell dimensions
    int cellWidth_;
    int cellHeight_;
};


#endif
