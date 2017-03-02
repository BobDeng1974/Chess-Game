//
//  HttpResponse.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef HttpResponse_hpp
#define HttpResponse_hpp

#include <iostream>

class HttpResponse
{
    public:
        HttpResponse();
        HttpResponse(long code, std::string body);
    
        virtual void setData(long code, std::string body);
    
        long getCode() const;
        std::string getBody() const;
    
    private:
        long code_ = 0;
        std::string body_= "";
};

#endif /* HttpResponse_hpp */
