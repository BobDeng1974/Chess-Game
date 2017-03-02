//
//  Screen.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Screen.hpp"

Screen::Screen(int windowWidth, int windowHeight, std::string windowName)
{
    this->windowWidth_ = windowWidth;
    this->windowHeight_ = windowHeight;
    this->windowName_ = windowName;
}

// Initializes all Screen components (window,buttons,sudoku)
bool Screen::init()
{
    bool success=true;
    
    // Initiate window (sdl, window, renderer, png, ttf)
    window_ = new Window(windowWidth_, windowHeight_, windowName_.c_str());
    if( !window_->init()){
        std::cerr << "Failed to initiate window\n";
        success = false;
    }
    // Get Screen Variables
    renderer_ = window_->getRenderer();
    return success;
}
