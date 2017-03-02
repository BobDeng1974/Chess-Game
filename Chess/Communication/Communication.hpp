//
//  Communication.hpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Communication_hpp
#define Communication_hpp

#include <iostream>

#include <curl/curl.h>

#include "HttpResponse.hpp"

class Communication
{
    public:
        Communication( std::string serverUrl);
        ~Communication();
    
        // Server Communication
        // Send a POST to the server on the resource, with content-type and body
        HttpResponse postServer(std::string resource, std::string contentType, std::string body);
        // Send a GET to the server on the resource
        HttpResponse getServer(std::string resource);

        // Peer-to-Peer Communication
    
        // Setters
        void setPeerIPv4Address(std::string IPv4Address);
        void setPeerIPv6Address(std::string IPv6Address);

    
    private:
        CURL *curl;
        CURLcode res;
    
        // urls
        std::string serverURL_;
        std::string peerIPv4Address_;
        std::string peerIPv6Address_;
    
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

};

#endif /* Communication_hpp */
