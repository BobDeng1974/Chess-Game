//
//  LogInScreen.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "LogInScreen.hpp"

LogInScreen::LogInScreen(int windowWidth, int windowHeight, std::string windowName) : Screen(windowWidth, windowHeight, windowName)
{}

// Initiates the Screen
bool
LogInScreen::init()
{
    // return variable
    bool success = true;
    
    if( (success=Screen::init())){
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

        if( success){
            //Initiate Buttons
            if(!loadButtons()){
                std::cerr << "Failed to load Buttons\n";
                success = false;
            }
            hasInitiated_ = true;
        }
    }
    return success;
}

// Screen main function
void
LogInScreen::start()
{
    // Verify if board initiated correctly
    if( !hasInitiated_) return;
    // Render Screen
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
                //handlerQueue_.push();
            }
        }
        // Process queue of handlers and see if required update window
        update = processHandlers();
        if( update){
            render();
        }
    }
}

// Load all buttons
bool
LogInScreen::loadButtons()
{
    int buttonWidth = windowWidth_/4;
    int buttonHeight = windowHeight_/5;
    int windowCenterX = windowWidth_/2;
    
    
    SelectorButton* newButton;
    std::string buttonName;

    
    
    // Create User Button
    buttonName = "Create User";
    newButton = new SelectorButton(renderer_ ,
                                   font_->getFont(24),
                                   windowCenterX - buttonWidth/2 ,  // X
                                   buttonHeight/2,                  // Y
                                   buttonWidth,                     // Width
                                   buttonHeight,                    // Height
                                   CREATE_USER);                    // Set onClick Value
    newButton->setText(buttonName);
    newButton->setCallbackEvent(Handler::EVENT_BUTTONCLICK);
    listButtons_.push_back(newButton);
    
    // Enter as Guest Button
    buttonName = "Enter as Guest";
    newButton = new SelectorButton(renderer_ ,
                                   font_->getFont(24),
                                   windowCenterX - buttonWidth/2 ,  // X
                                   buttonHeight/2 + buttonHeight,   // Y
                                   buttonWidth,                     // Width
                                   buttonHeight,                    // Height
                                   ENTER_AS_GUEST);                    // Set onClick Value
    newButton->setText(buttonName);
    newButton->setCallbackEvent(Handler::EVENT_BUTTONCLICK);
    listButtons_.push_back(newButton);

    
    return true;
}

// Process all handlers
bool LogInScreen::processHandlers()
{
    bool success = false;
    
    while( !handlerQueue_.empty()){
        Handler handler = handlerQueue_.front();
        handlerQueue_.pop();
        
        switch (handler.getEvent())
        {
            case Handler::EVENT_INPUT:
                success = true;
                break;
           
            default:
                break;
        }
    }
    return success;
}

// Render screen
void LogInScreen::render()
{
    // Clear window
    window_->clearScreen();
    
    // Render Elements
    
    
    // Render options buttons
    
    // Update Screen
    window_->updateScreen();
}


