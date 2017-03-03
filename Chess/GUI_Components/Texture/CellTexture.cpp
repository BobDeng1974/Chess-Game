//
//  Texture.cpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 17/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "CellTexture.hpp"

CellTexture::CellTexture( SDL_Renderer* renderer, int cellWidth, int cellHeight){
    //Initialize
    mTexture_ = NULL;
    this->cellWidth_ = cellWidth;
    this->cellHeight_ = cellHeight;
    this->renderer_ = renderer;
    
    for(int i = 0; i<imageNo_; i++){
        gSpriteClips[ i ].x = cellWidth*i;
        gSpriteClips[ i ].y = 0;
        gSpriteClips[ i ].w = cellWidth;
        gSpriteClips[ i ].h = cellHeight;
    }
}

CellTexture::~CellTexture(){
    //Deallocate
    free();
};



// Creates Texture from files, Can colorkey
bool CellTexture::loadFromFile(std::string path, bool hasColorkey, uint8_t red , uint8_t green , uint8_t blue )
{
    
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //Color key image if set
        if ( hasColorkey) SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, red, green, blue ) );
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer_, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    //Return success
    mTexture_ = newTexture;
    return mTexture_ != NULL;
}

// Render Texture
void CellTexture::render( int x, int y, CellTexture::PieceType piecetype )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, cellHeight_, cellWidth_ };
    
    //Render to screen
    SDL_RenderCopy( renderer_, mTexture_, &gSpriteClips[piecetype] , &renderQuad);
}


// Setters for modes
void CellTexture::setBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture_, blending );
}

void CellTexture::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture_, alpha );
}

void CellTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture
    SDL_SetTextureColorMod( mTexture_, red, green, blue );
};

void CellTexture::setDimensions(int width, int height)
{
    this->cellWidth_ = width;
    this->cellHeight_ = height;
}

// Free texture
void CellTexture::free()
{
    //Free texture if it exists
    if( mTexture_ != NULL )
    {
        SDL_DestroyTexture( mTexture_ );
        mTexture_ = NULL;
        cellWidth_ = 0;
        cellHeight_ = 0;
    }
}



