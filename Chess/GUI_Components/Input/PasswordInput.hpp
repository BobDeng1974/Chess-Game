//
//  PasswordInput.hpp
//  Chess
//
//  Created by Ricardo Martins on 05/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef PasswordInput_hpp
#define PasswordInput_hpp

#include "BaseInput.hpp"


class PasswordInput : public BaseInput
{
    public:
        PasswordInput(SDL_Renderer* renderer,TTF_Font* font);
        PasswordInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height);
        
        // handle event on button
        virtual Handler handleEvent( SDL_Event *e);
        
        // interface render
        virtual void render();
    
    private:
        std::string passwordText_;
};

#endif /* PasswordInput_hpp */
