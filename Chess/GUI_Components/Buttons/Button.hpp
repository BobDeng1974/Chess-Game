//
//  Button.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 16/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Handler.hpp"

class Button
{
    public:
        // Constructors with renderer required
        Button(SDL_Renderer* renderer,TTF_Font* font);
        Button(SDL_Renderer* renderer,TTF_Font* font, int x, int y);
    
        // set 2D position of button
        void setPosition( int x, int y);
    
        // set button's text
        bool setText(std::string text);
    
        // set Text's color
        void setTextColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    
        // handle event on button
        virtual Handler handleEvent( SDL_Event *e) = 0;
    
        // interface render
        virtual void render() = 0;
    
        // reset button to initial state
        virtual void reset(){};
    
        // State Setters
        void setVisibility( bool visibility);
        void setEnabled( bool enabled);
    
        // Getters of State
        bool getVisibility() const;
        bool getEnabled() const;
    
    protected:
        // button location
        SDL_Point anchorPoint_;
    
        // Window Renderer
        SDL_Renderer* renderer_;
        // Text font
        TTF_Font* font_;
    
        // Button Texture
        Texture* texture_=nullptr;
    
        // Text color
        SDL_Color textColor = { 0, 0, 0, 0xFF };
    
        // State Indicators
        bool isVisible_ = true;
        bool isEnabled_ = true;

};

#endif /* Button_hpp */
