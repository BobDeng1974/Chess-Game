//
//  HttpResponse.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "HttpResponse.hpp"

HttpResponse::HttpResponse(){}

HttpResponse::HttpResponse(long code, std::string body)
{
    setData(code, body);
}

void HttpResponse::setData(long code, std::string body)
{
    this->code_ = code;
    this->body_ = body;
}

std::string HttpResponse::getBody() const { return this->body_; }

long HttpResponse::getCode() const { return this->code_; }
