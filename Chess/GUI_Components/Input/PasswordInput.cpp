//
//  PasswordInput.cpp
//  Chess
//
//  Created by Ricardo Martins on 05/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "PasswordInput.hpp"

PasswordInput::PasswordInput(SDL_Renderer* renderer,TTF_Font* font) : BaseInput(renderer, font)
{ }

PasswordInput::PasswordInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height) : BaseInput(renderer, font, x, y, width, height)
{ }

// handle input
Handler
PasswordInput::handleEvent(SDL_Event *e)
{
    Handler handler(Handler::EVENT_IGNORE);
    bool renderText = false;
    //Special key input
    if( e->type == SDL_KEYDOWN && focused_)
    {
        //Handle backspace
        if( e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
            //lop off character
            passwordText_.pop_back();
            renderText = true;
        }
        //Handle copy
        else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( passwordText_.c_str() );
        }
        //Handle paste
        else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            passwordText_ = SDL_GetClipboardText();
            renderText = true;
        }
    }
    //Special text input event
    else if( e->type == SDL_TEXTINPUT && focused_)
    {
        //Not copy or pasting
        if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
        {
            //Append character
            passwordText_ += e->text.text;
            renderText = true;
        }
    }else if( e->type == SDL_MOUSEBUTTONDOWN) { //If mouse event happened
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        
        //Check if mouse is in button
        bool inside = true;
        
        //Mouse is left of the button
        if( x < anchorPoint_.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > anchorPoint_.x + width_ )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < anchorPoint_.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > anchorPoint_.y + height_ )
        {
            inside = false;
        }
        
        if(inside){
            focused_ = true;
            handler.setEvent(Handler::EVENT_INPUT);
        }else{
            if(focused_)
                handler.setEvent(Handler::EVENT_INPUT);
            focused_=false;
        }
    }
    
    if( renderText){
        loadTextTexture();
        handler.setEvent(Handler::EVENT_INPUT);
    }
    return handler;
}

// Render  TextInput
void
PasswordInput::render()
{
    inputText = std::string( passwordText_.size(), '*' );
    loadTextTexture();
    BaseInput::render();
}



