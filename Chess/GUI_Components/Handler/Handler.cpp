//
//  Handler.cpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 19/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Handler.hpp"

Handler::Handler(){}

Handler::Handler( Handler::Event event)
{
    setEvent(event);
}

// Setters
void Handler::setEvent(Handler::Event event){ this->event_ = event; }
void Handler::setIntExtra(int extra){ this->intExtra_ = extra; }

// Getters
Handler::Event Handler::getEvent() const { return event_; }
int Handler::getIntExtra() const { return intExtra_; }
