//
//  SelectorButton.cpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 19/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "SelectorButton.hpp"

SelectorButton::SelectorButton(SDL_Renderer* renderer, TTF_Font* font, int type)
: RectButton(renderer,font)
{
    this->type_ = type;
}

SelectorButton::SelectorButton(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int width, int height, int type)
: RectButton(renderer,font, x, y, width, height)
{
    this->type_ = type;
}

// Handles input events, inserts button specific int
Handler SelectorButton::handleEvent(SDL_Event *e)
{
    // return Handler set from inherited class
    Handler handler = inherited_::handleEvent(e);
    
    // Add type as Extra
    handler.setIntExtra(type_);
    
    return handler;
}
