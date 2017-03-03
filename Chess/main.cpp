//
//  main.cpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//
#include <SDL2/SDL.h>

#include <iostream>

#include "LogInScreen.hpp"
#include "ChessScreen.hpp"
#include "Communication.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, const char * argv[])
{
    
    bool success = false;
    
    // Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else{
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            std::cerr << "Warning: Linear texture filtering not enabled!\n";
        }
    }
    
    LogInScreen* login = new LogInScreen(400 , 150, "Log in");
    if( login->init() ){
        login->start();
    }
    if( login->isAuthenticated()){
        //Create Resolution Screen
        ChessScreen* chessScreen = new ChessScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        
        // Initiate Screen for resolution selection
        if( chessScreen->init() ){
            chessScreen->start();
        }
    }
    return 0;
}
