//
//  ChessScreen.hpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef ChessScreen_hpp
#define ChessScreen_hpp


#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <queue>

#include "Window.hpp"
#include "Font.hpp"
#include "Handler.hpp"
#include "Chess.hpp"

class ChessScreen
{
    public:
        ChessScreen(int windowWidth, int windowHeight);
        
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
        // Screen Size
        int windowWidth_;
        int windowHeight_;
        
        // Window variable
        Window* window_=nullptr;
        // Screen Renderer
        SDL_Renderer* renderer_ = nullptr;
        //TTF font
        Font* font_ = nullptr;
        // CellTexture container
        CellTexture* cellTexture_ = nullptr;
        // Chess game
        Chess* chess_ = nullptr;
    
        // List of Handlers (event tracker)
        std::queue<Handler> handlerQueue_;

        bool hasInitiated=false;   // Bool indicates if initiated correctly

    
};

#endif /* ChessScreen_hpp */
