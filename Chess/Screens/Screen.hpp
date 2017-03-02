//
//  Screen.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <iostream>

#include "Window.hpp"
#include "Font.hpp"

class Screen
{
public:
    Screen(int windowWidth, int windowHeight, std::string windowName);
    
    // Initialize Screen
    virtual bool init();
    
     // Start Screen Functions
    virtual void start() = 0;
    
protected:
    // Screen Size
    int windowWidth_;
    int windowHeight_;
    // Window variable
    Window* window_=nullptr;
    std::string windowName_;
    // Screen Renderer
    SDL_Renderer* renderer_ = nullptr;
    
    // Render screen
    virtual void render() = 0;
};

#endif /* Screen_hpp */
