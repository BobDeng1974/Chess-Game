//
//  Texture.cpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 17/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture( SDL_Renderer* renderer){
    //Initialize
    mTexture_ = NULL;
    mWidth = 0;
    mHeight = 0;
    this->renderer_ = renderer;
}

Texture::Texture( SDL_Renderer* renderer, TTF_Font* font)
{
    //Initialize
    mTexture_ = NULL;
    mWidth = 0;
    mHeight = 0;
    this->renderer_ = renderer;
    this->font_ = font;
}

Texture::~Texture(){
    //Deallocate
    free();
};

// Creates Texture from files, Can colorkey
bool Texture::loadFromFile(std::string path, bool hasColorkey, uint8_t red , uint8_t green , uint8_t blue )
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
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    mTexture_ = newTexture;
    return mTexture_ != NULL;
}

// Load text texture
bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //SDL_Color bgColor = { 0, 0xFF, 0xFF };
    
    
    //Render text surface
    //SDL_Surface* textSurface = TTF_RenderText_Shaded( gFont, textureText.c_str(), textColor , bgColor );
    SDL_Surface* textSurface = TTF_RenderText_Blended( font_ , textureText.c_str(), textColor );
    
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture_ = SDL_CreateTextureFromSurface( renderer_, textSurface );
        if( mTexture_ == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture_ != NULL;
}

// Render Texture on Rect
void
Texture::render( SDL_Rect renderQuad )
{
    //Render to screen
    SDL_RenderCopy( renderer_, mTexture_, 0 , &renderQuad);
}

// Render Texture
void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopyEx( renderer_, mTexture_, clip, &renderQuad, angle, center, flip );
}


// Setters for modes
void Texture::setBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture_, blending );
}

void Texture::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture_, alpha );
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture
    SDL_SetTextureColorMod( mTexture_, red, green, blue );
};

// Free texture
void Texture::free()
{
    //Free texture if it exists
    if( mTexture_ != NULL )
    {
        SDL_DestroyTexture( mTexture_ );
        mTexture_ = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}



