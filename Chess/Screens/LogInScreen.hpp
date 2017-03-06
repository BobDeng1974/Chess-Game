//
//  LogInScreen.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef LogInScreen_hpp
#define LogInScreen_hpp

#include <iostream>
#include <queue>

#include "Screen.hpp"
#include "Font.hpp"
#include "Handler.hpp"
#include "SelectorButton.hpp"
#include "TextInput.hpp"
#include "PasswordInput.hpp"
#include "Communication.hpp"

#include "json.hpp"
#include "HttpResponse.hpp" 

#define CREATE_USER 1
#define ENTER_AS_GUEST 2
#define AUTHENTICATE 3

class LogInScreen : public Screen
{
    public:
        LogInScreen(int windowWidth, int windowHeight, std::string windowName);
    
        // Initialize Screen
        bool init();
    
        // Start Screen Functions
        void start();
    
        // Getter to see if user is authenticaed
        bool isAuthenticated() const;
    
    protected:
        // Load Screen Buttons
        virtual bool loadButtons();
        
        //Process Handlers
        virtual bool processHandlers();
        
        // Render screen
        virtual void render();
    
    private:
        //TTF font
        Font* font_ = nullptr;

        // GUI_Components on the screen
        std::vector<Button*> listButtons_;      // list of buttons
        TextInput* usernameInput_ = nullptr;    // TextInput for username
        PasswordInput* passwordInput_ = nullptr;    // TextInput for username

        // List of Handlers (event tracker)
        std::queue<Handler> handlerQueue_;
    
        // Communications class
        Communication* comms_;
    
        bool hasInitiated_ = false;   // Bool indicates if initiated correctly
        bool hasAuthenticated_ = false; // Bool indicates if Login process has completed
    
        // Authenticates user or log in as guest
        bool CreateUser( bool isGuest);
        bool authenticateUser();
};

#endif /* LogInScreen_hpp */
