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
        // Creates different sized fonts1
        font_->createSizedFont(24);
        font_->createSizedFont(20);
        font_->createSizedFont(16);

        if( success){
            //Initiate Buttons
            if(!loadButtons()){
                std::cerr << "Failed to load Buttons\n";
                success = false;
            }
            
            comms_ = new Communication("localhost:3000");
            
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
    
    int alpha = 255;
    while( !quit && !hasAuthenticated_){
        while( SDL_PollEvent( &e) != 0 ){
            if( e.type == SDL_QUIT){
                quit = true;
            }
            else{
                
              
                // Pass event onto buttons
                for( Button* button: listButtons_) handlerQueue_.push(button->handleEvent(&e));
                // Pass event onto username TextInput
                handlerQueue_.push(usernameInput_->handleEvent(&e));
                handlerQueue_.push(passwordInput_->handleEvent(&e));
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
    int buttonWidth = windowWidth_*3/4;
    int buttonHeight = windowHeight_/7;
    int windowCenterX = windowWidth_/2;
    int spacing = windowHeight_*2/25;
    
    // Create UserName input box
    usernameInput_ = new TextInput(renderer_,
                                   font_->getFont(20),
                                   windowCenterX - buttonWidth/2 ,  // X
                                   spacing,                         // Y
                                   buttonWidth,                     // Width
                                   buttonHeight);
    usernameInput_->setPlaceHolder("username", '0');
    
    // Create UserName input box
    passwordInput_ = new TextInput(renderer_,
                                   font_->getFont(20),
                                   windowCenterX - buttonWidth/2 ,  // X
                                   buttonHeight + (2*spacing),    // Y
                                   buttonWidth,                     // Width
                                   buttonHeight);
    passwordInput_->setPlaceHolder("password", '0');

    
    SelectorButton* newButton;
    std::string buttonName;
    // Create User Button
    buttonName = "Register";
    newButton = new SelectorButton(renderer_ ,
                                   font_->getFont(16),
                                   windowCenterX - buttonWidth/2 ,  // X
                                   (2*buttonHeight) + (3*spacing),  // Y
                                   buttonWidth*2/5,                 // Width
                                   buttonHeight,                    // Height
                                   CREATE_USER);                    // Set onClick Value
    newButton->setText(buttonName);
    newButton->setStretch(false);
    newButton->setCallbackEvent(Handler::EVENT_BUTTONCLICK);
    listButtons_.push_back(newButton);
    
    // Log in Button
    buttonName = "Log in";
    newButton = new SelectorButton(renderer_ ,
                                   font_->getFont(16),
                                   windowCenterX - buttonWidth/2 + (buttonWidth*3/5) ,// X
                                   (2*buttonHeight) + (3*spacing),      // Y
                                   buttonWidth*2/5,                     // Width
                                   buttonHeight,                        // Height
                                   AUTHENTICATE);                     // Set onClick Value
    newButton->setText(buttonName);
    newButton->setStretch(false);
    newButton->setCallbackEvent(Handler::EVENT_BUTTONCLICK);
    listButtons_.push_back(newButton);
    
    // Log in as Guest Button
    buttonName = "Enter as Guest";
    newButton = new SelectorButton(renderer_ ,
                                   font_->getFont(16),
                                   windowCenterX - buttonWidth/2 ,// X
                                   (3*buttonHeight) + (4*spacing),      // Y
                                   buttonWidth,                         // Width
                                   buttonHeight,                        // Height
                                   ENTER_AS_GUEST);                     // Set onClick Value
    newButton->setText(buttonName);
    newButton->setStretch(false);
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
            case Handler::EVENT_INPUT :
                success = true;
                break;
                
            case Handler::EVENT_RENDER:
                success = true;
                break;
                
            case Handler::EVENT_BUTTONCLICK :
                int buttonID = handler.getIntExtra();
                switch (buttonID) {
                    case CREATE_USER:{
                        if(!CreateUser(false))
                            // Show error message
                            hasAuthenticated_=true;
                        else
                            hasAuthenticated_=true;
                        break;
                    }
                    case ENTER_AS_GUEST:{
                        if(!CreateUser(true))
                            // Show error message
                            hasAuthenticated_=true;
                        else
                            hasAuthenticated_=true;
                        break;
                    }
                    case AUTHENTICATE:{
                        //authenticateUser();
                        // hasAuthenticated_ set
                        break;
                    }
                }
                break;
        }
    }
    return success;
}

// Render screen
void
LogInScreen::render()
{
    // Clear window
    window_->clearScreen();
    
    // Render Elements
    
    
    // Render options buttons
    for( Button* button: listButtons_) button->render();
    
    usernameInput_->render();
    passwordInput_->render();
    // Update Screen
    window_->updateScreen();
}

bool
LogInScreen::isAuthenticated()const { return hasAuthenticated_; }

// Private Functions
// Authenticates User or Login as Guest
bool
LogInScreen::CreateUser(bool isGuest)
{
    bool succes = false;
    nlohmann::json data;
    data["username"] = (isGuest)?"Guest": usernameInput_->getText();
    if(isGuest)
        data["password"] = "passworkNotImplemented";
    std::string body = data.dump();
    HttpResponse response = comms_->postServer("/users", "application/json", body);
    data = nlohmann::json::parse(response.getBody());
    switch (response.getCode()) {
        case 200:
            std::cout << "Log In OK:\n" << data["username"] << " has id = " << data["id"] << std::endl;
            succes = true;
            break;
            
        case 400:
            std::cout << "Log In NOK:\n" << data["message"] << std::endl;
            break;
            
        case 409:
            std::cout << "Username already exists.\n" <<data["message"] << std::endl;
            break;
            
        default:
            std::cout << "Unknown error code\n" << std::endl;
            break;
    }
    return succes;
}

// Authenticates User or Login as Guest
bool
LogInScreen::authenticateUser()
{
    bool succes = false;
    nlohmann::json data;
    data["password"] = "passworkNotImplemented";
    std::string body = data.dump();
    std::string path = "/users/";
    path.append(usernameInput_->getText());
    HttpResponse response = comms_->postServer(path, "application/json", body);
    data = nlohmann::json::parse(response.getBody());
    switch (response.getCode()) {
        case 200:
            std::cout << "Log In OK:\n" << data["username"] << " has id = " << data["id"] << std::endl;
            succes = true;
            break;
            
        case 404:
            std::cout << "Username not existant:\n" << data["message"] << std::endl;
            break;
            
        case 409:
            std::cout << "Password Incorrect\n" <<data["message"] << std::endl;
            break;
            
        default:
            std::cout << "Unknown error code\n" << std::endl;
            break;
    }
    return succes;
}



