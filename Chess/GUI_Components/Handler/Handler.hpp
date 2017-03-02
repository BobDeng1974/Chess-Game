//
//  Handler.hpp
//  Sudoku_Game
//
//  Created by Ricardo Martins on 19/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Handler_hpp
#define Handler_hpp

#include <stdio.h>

class Handler
{
    public:
        // Existent types of events
        enum Event{ EVENT_IGNORE, EVENT_INPUT, EVENT_BUTTONCLICK, EVENT_RENDER};

        Handler();
        Handler( Handler::Event event);
    
        // Setters
        void setEvent(Handler::Event event);
        void setIntExtra(int extra);
    
        // Getters
        Handler::Event getEvent() const;
        int getIntExtra()const;
    
    private:
        Event event_;
    
        int intExtra_;
};

#endif /* Handler_hpp */
