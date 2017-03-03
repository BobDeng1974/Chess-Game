//
//  RectButton.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 17/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef RectButton_hpp
#define RectButton_hpp

#include <iostream>

#include "Button.hpp"
#include "Handler.hpp"

class RectButton : public Button
{
    public:
        RectButton(SDL_Renderer* renderer, TTF_Font* font);
        RectButton(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int width, int height);
    
        // handle Events
        virtual Handler handleEvent(SDL_Event *e);
    
        // render button
        void render();
    
        // Sets Button functionality
        void setCallbackEvent( Handler::Event event);
    
        // reset button state
        void reset();
    
        // Set toggle behaviour
        void setToggle( bool toggle);
        void setStretch(  bool stretch);
    
    protected:
        int width_;
        int height_;
    
        // Indicates if button was clicked
        bool isClicked_ = false;
        bool isInside_ = false;
        // indicates is it should toggle
        bool hasToggleCapacity_ = false;
        bool stretched_ = false;
        // indicates event to be pushed on clicked
        Handler::Event event_ = Handler::EVENT_IGNORE;
  
};


#endif /* RectangleButton_hpp */
