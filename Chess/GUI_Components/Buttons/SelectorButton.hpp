//
//  SelectorButton.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 19/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef SelectorButton_hpp
#define SelectorButton_hpp

#include "RectButton.hpp"

class SelectorButton : public RectButton
{
public:
    SelectorButton(SDL_Renderer* renderer, TTF_Font* font, int type);
    SelectorButton(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int width, int height, int type);
    
    // handle event
    virtual Handler handleEvent(SDL_Event *e);

private:
    typedef RectButton inherited_;
    // button specific int indicates difficulty
    int type_;

};
#endif /* SelectorButton_hpp */
