//
//  TextInput.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "TextInput.hpp"

TextInput::TextInput(SDL_Renderer* renderer,TTF_Font* font) : BaseInput(renderer, font)
{ }

TextInput::TextInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height) : BaseInput(renderer, font, x, y, width, height)
{ }

// handle input
Handler
TextInput::handleEvent(SDL_Event *e)
{
    Handler handler(Handler::EVENT_IGNORE);
    bool renderText = false;
    //Special key input
    if( e->type == SDL_KEYDOWN )
    {
        //Handle backspace
        if( e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
            //lop off character
            inputText.pop_back();
            renderText = true;
        }
        //Handle copy
        else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( inputText.c_str() );
        }
        //Handle paste
        else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            inputText = SDL_GetClipboardText();
            renderText = true;
        }
    }
    //Special text input event
    else if( e->type == SDL_TEXTINPUT )
    {
        //Not copy or pasting
        if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
        {
            //Append character
            inputText += e->text.text;
            renderText = true;
        }
    }
    if( renderText)
        handler.setEvent(Handler::EVENT_INPUT);
    return handler;
}

// Render  TextInput
void
TextInput::render()
{
    BaseInput::render();
}

