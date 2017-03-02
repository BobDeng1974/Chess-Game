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
#include 

class LogInScreen : public Screen
{
    public:
        LogInScreen(int windowWidth, int windowHeight, std::string windowName);
    
        // Initialize Screen
        bool init();
    
        // Start Screen Functions
        void start();
    
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

        // List of Handlers (event tracker)
        std::queue<Handler> handlerQueue_;
    
        bool hasInitiated_ = false;   // Bool indicates if initiated correctly

};

#endif /* LogInScreen_hpp */
