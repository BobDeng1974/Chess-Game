//
//  Font.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 20/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp

#include <string>
#include <map>

#include <SDL2_ttf/SDL_ttf.h>
class Font
{
public:
    Font( std::string filename_);
    ~Font();
    
    // Create font from path with size
    bool createSizedFont(int size);
    
    // get font with size
    TTF_Font* getFont(int size);
    
private:
    // Based font
    std::string path_;
  
    // Map with all loaded fonts
    std::map<int, TTF_Font* > fonts_;
};

#endif /* Font_hpp */
