//
//  TextInput.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef TextInput_hpp
#define TextInput_hpp

#include <iostream>

#include "BaseInput.hpp"

class TextInput : public BaseInput
{
    public:
        TextInput(SDL_Renderer* renderer,TTF_Font* font);
        TextInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height);

        // handle event on button
        virtual Handler handleEvent( SDL_Event *e);
        
        // interface render
        virtual void render();
    
    private:
        
};

#endif /* TextInput_hpp */
