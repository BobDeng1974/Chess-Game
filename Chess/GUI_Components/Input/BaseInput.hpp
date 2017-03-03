//
//  BaseInput.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef BaseInput_hpp
#define BaseInput_hpp

#include <iostream>

#include <SDL2/SDL.h>

#include "Font.hpp"
#include "Texture.hpp"
#include "Handler.hpp"

class BaseInput
{
    public:
        BaseInput(SDL_Renderer* renderer,TTF_Font* font);
        BaseInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height);
    
        // set 2D position of button
        void setPosition( int x, int y, int width, int height);
    
        // set Input's text
        void setText(std::string text);
    
        // set Text's color
        void setTextColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    
        // handle event on button
        virtual Handler handleEvent( SDL_Event *e) = 0;
    
        // interface render
        virtual void render();
        
        // reset button to initial state
        virtual void reset();
        
        // State Setters
        void setVisibility( bool visibility);
        void setClickable( bool clickable);
        
        // Getters of State
        bool isVisible() const;
        bool isClickable() const;


    protected:
        // button location
        SDL_Point anchorPoint_;
        int width_;
        int height_;
    
        // Window Renderer
        SDL_Renderer* renderer_;
        // Text font
        TTF_Font* font_;
        
        // Text Texture
        Texture* texture_=nullptr;
    
        // Text
        std::string inputText;
    
        // Text color
        SDL_Color textColor = { 0, 0, 0, 0xFF }; // Black by default
    
        // State Indicators
        bool visible_ = true;
        bool clickable_ = true;
    
        // loads text into texture
        void loadTextTexture(); 

    
};

#endif /* BaseInput_hpp */
