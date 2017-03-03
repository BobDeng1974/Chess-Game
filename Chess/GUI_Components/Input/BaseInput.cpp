//
//  BaseInput.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "BaseInput.hpp"

BaseInput::BaseInput(SDL_Renderer* renderer,TTF_Font* font)
{
    this->renderer_ = renderer;
    this->font_ = font;
    texture_ = new Texture(renderer_, font);
}
BaseInput::BaseInput(SDL_Renderer* renderer,TTF_Font* font, int x, int y, int width, int height)
{
    this->renderer_ = renderer;
    this->font_ = font;
    texture_ = new Texture(renderer_, font);
    setPosition(x, y, width, height);
}

// Renders the outside box and the text
void
BaseInput::render()
{
    if( !visible_) return;
    
    //Render border
    SDL_Rect inputRect = { anchorPoint_.x, anchorPoint_.y, width_, height_ };
    SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRect( renderer_, &inputRect );
    
    // render text inside box
    if(texture_!=nullptr)
        texture_->render( inputRect );
}

void
BaseInput::setPosition(int x, int y, int width, int height)
{
    this->anchorPoint_.x = x;
    this->anchorPoint_.y = y;
    this->width_ = width;
    this->height_ = height;
}

// Sets text color
void
BaseInput::setTextColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    textColor = {red, green, blue, alpha};
    loadTextTexture();
}

// Sets text
void
BaseInput::setText(std::string text) { this->inputText = text; }

// Reset the Text
void
BaseInput::reset()
{
    setText(std::string());
}

// Setters
void
BaseInput::setClickable(bool clickable) { this->clickable_ = clickable; }
void
BaseInput::setVisibility(bool visible) { this->visible_ = visible; }

// Getters
bool
BaseInput::isClickable() const { return clickable_; }
bool
BaseInput::isVisible() const { return visible_; }


// Private Methods

// Sets text
void
BaseInput::loadTextTexture()
{
    if( texture_!=nullptr){
        texture_->loadFromRenderedText(inputText, textColor );
    }
}
