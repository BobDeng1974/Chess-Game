//
//  ChessScreen.cpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "ChessScreen.hpp"

ChessScreen::ChessScreen(int windowWidth, int windowHeight)
{
    this->windowWidth_ = windowWidth;
    this->windowHeight_ = windowHeight;
}

// Screen main function
void ChessScreen::start()
{
    // Initialize elements
    if( !hasInitiated) return;
    render();
    
    // User wants to Quit
    bool quit = false;
    
    // Required to update window
    bool update = true;
    
    // Event Handler
    SDL_Event e;
    
    while( !quit){
        while( SDL_PollEvent( &e) != 0 ){
            if( e.type == SDL_QUIT){
                quit = true;
            }
            else{
                    // TODO input handling
            }
        }
        
        // Process queue of handlers and see if required update window
        update = processHandlers();
        if( update){
            render();
        }
    }
}


// Initializes all Screen components (window,buttons,sudoku)
bool ChessScreen::init()
{
    bool success=true;
    
    // Initiate window (sdl, window, renderer, png, ttf)
    window_ = new Window(windowWidth_, windowHeight_, "Sudoku");
    if( !window_->init()){
        std::cerr << "Failed to initiate window\n";
        success = false;
    }
    
    // Get Screen Variables
    renderer_ = window_->getRenderer();
    
    // Create font class
    font_ = new Font("Images/font2.ttf");
    if( !font_->createSizedFont(28)){
        std::cerr << " Failed to load font\n";
        success = false;
    }
    // Creates different sized fonts
    font_->createSizedFont(24);
    font_->createSizedFont(20);
    font_->createSizedFont(16);
    font_->createSizedFont(12);
    
    cellTexture_ = new CellTexture(renderer_, 80,80);
    if(!cellTexture_->loadFromFile("Images/pieces.png")){
        std::cerr << " Failed to load pieces\n";
        success = false;
    }
    
    if( success){
        //Initiate Buttons
        if(!loadButtons()){
            std::cerr << "Failed to load Buttons\n";
            success = false;
        }
        
        // Create Chess
        chess_ = new Chess(renderer_, cellTexture_, windowWidth_, windowHeight_);
        hasInitiated = true;
    }
    
    return success;
}

// Load all buttons
bool ChessScreen::loadButtons(){
    
    return true;
}


// Process all handlers
bool ChessScreen::processHandlers()
{
    bool success = false;
    
    while( !handlerQueue_.empty()){
        Handler handler = handlerQueue_.front();
        handlerQueue_.pop();
        
        switch (handler.getEvent())
        {
            case Handler::EVENT_INPUT:
                break;
            case Handler::EVENT_IGNORE:
                break;
        }
    }
    return success;
}

// Render screen
void ChessScreen::render()
{
    // Clear window
    window_->clearScreen();
    
    // Render Elements
    chess_->render();
    
    // Render options buttons
    
    // Update Screen
    window_->updateScreen();
}



