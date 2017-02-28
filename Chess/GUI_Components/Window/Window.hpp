//
//  Window.hpp
//  Sudoku
//
//  Created by Ricardo Martins on 15/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>

class Window
{
    public:
        Window(int windowWidth, int windowHeight, const char* windowTitle, int bgR = 0xff, int bgG = 0xff, int bgB = 0xff);
        ~Window();
    
        // initialize support libraries
        virtual bool init();
    
    
        // Clear screen
        void clearScreen();
    
        // Update screen
        void updateScreen();
    
        // Getters
        SDL_Renderer* getRenderer() const;
    
    protected:
        // Initialisers for support frameworks
        bool initPNG();
        bool initTTF();
    
    private:
        // Window Variables for size and background
        int screenWidth_;
        int screenHeight_;
        int bgR_;
        int bgG_;
        int bgB_;
        std::string title;
    
        // Window
        SDL_Window* window_ = nullptr;
        // Renderer
        SDL_Renderer* renderer_ = nullptr;

        // support libraries booleans
        bool isPNGActive_=false;
        bool isTTFActive_=false;
};




#endif /* Window_hpp */
