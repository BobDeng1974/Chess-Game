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

class Texture
{
public:
    //Initializes variables
    Texture( SDL_Renderer* renderer);
    Texture( SDL_Renderer* renderer, TTF_Font* font);
    
    //Deallocates memory
    ~Texture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path , bool hasColorkey=false, uint8_t red = 0xFF, uint8_t green = 0xFF, uint8_t blue = 0xFF);
    
    // Loads texture from Text
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    
    // Set Texture Properties
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Getters image dimensions
    int getWidth(){     return mWidth;  };
    int getHeight(){    return mHeight; };
    
    //Deallocates texture
    void free();

private:
    //The actual hardware texture
    SDL_Texture* mTexture_;
    
    SDL_Renderer* renderer_=nullptr;
    TTF_Font* font_ = NULL;

    //Image dimensions
    int mWidth;
    int mHeight;
};


#endif
