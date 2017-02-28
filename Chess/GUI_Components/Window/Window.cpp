//
//  Window.cpp
//  Sudoku
//
//  Created by Ricardo Martins on 15/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Window.hpp"

Window::Window(int windowWidth, int windowHeight, const char* windowTitle, int bgR, int bgG, int bgB){
    this->screenWidth_ = windowWidth;
    this->screenHeight_ = windowHeight;
    this->bgR_ = bgR;
    this->bgG_ = bgG;
    this->bgB_ = bgB;
    this->title = windowTitle;
}

Window::~Window()
{
    //Destroy window
    SDL_DestroyRenderer( renderer_ );
    SDL_DestroyWindow( window_ );
    window_ = NULL;
    renderer_ = NULL;
    
    //Quit SDL subsystems
    if( isPNGActive_)IMG_Quit();
    if( isTTFActive_)TTF_Quit();
}

// Initializes window
bool Window::init()
{
    bool success = true;
    // Creates window
    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_SHOWN);
    if(window_==nullptr){
        std::cerr <<  "Window could not be created! SDL_Error: "<< SDL_GetError() << std::endl;
        success = false;
    }
    else{
        // Create renderer
        renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( renderer_ == nullptr){
            std::cerr << "Renderer coundn't be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else{
            //Initialize renderer color
            SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
            
            if( !initPNG()) success = false;
            
            if( !initTTF()) success = false;
        }
    }    
    return success;
}

// Clears Window
void Window::clearScreen()
{
    //Clear screen
    SDL_SetRenderDrawColor( renderer_, bgR_, bgG_, bgB_, 0xFF );
    SDL_RenderClear( renderer_ );
}
// Updates Screen
void Window::updateScreen()
{
    //Update screen
    SDL_RenderPresent( renderer_ );
}
// Initializes PNG Support
bool Window::initPNG()
{
    if (isPNGActive_)return true;
    
    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init(imgFlags) & imgFlags)){
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    isPNGActive_=true;
    return true;
}
// Initializes TTF support
bool Window::initTTF()
{
    if( isTTFActive_) return true;
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    isTTFActive_=true;
    return true;
}

// Getter for the renderer
SDL_Renderer* Window::getRenderer() const { return renderer_; }


