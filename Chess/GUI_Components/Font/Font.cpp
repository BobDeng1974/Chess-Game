//
//  Font.cpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 20/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Font.hpp"

Font::Font( std::string path)
{
    this->path_ = path;
}

Font::~Font()
{
    // Delete all fonts created
    for (auto it=fonts_.begin(); it!=fonts_.end(); ++it){
        TTF_CloseFont( it->second );
    }
}

// Create Font with size
bool Font::createSizedFont(int size)
{
    // return bool
    bool success = true;
    if (fonts_.find(size) == fonts_.end() ) {
        TTF_Font* font = TTF_OpenFont( path_.c_str(), size );
        if( font==nullptr){
            success=false;
        }else{
            fonts_[size] = font;
        }
    }
    return success;
}
// Getter for font with size
TTF_Font* Font::getFont(int size)
{
    if(fonts_.find(size) == fonts_.end()) return nullptr;
    else return fonts_[size];
}
