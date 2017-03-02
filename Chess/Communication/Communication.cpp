//
//  Communication.cpp
//  Chess
//
//  Created by Ricardo Martins on 02/03/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Communication.hpp"

Communication::Communication(std::string serverUrl)
{
    // In windows, this will init the winsock stuff
    curl_global_init(CURL_GLOBAL_ALL);
    // Set server url
    this->serverURL_ = serverUrl;
}

Communication::~Communication()
{
    curl_easy_cleanup(curl);
}

HttpResponse Communication::postServer(std::string resource, std::string contentType, std::string body)
{
    // return variable
    HttpResponse response;
    
    // Init curl
    curl = curl_easy_init();
    if(!curl) // If fails, return
        return response;
    
    // Set full path
    std::string path(serverURL_);
    path.append(resource);
    // Set curl complete url
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // Set headers
    struct curl_slist *headers=nullptr;
    std::string accept("Accept: ");
    accept.append(contentType);
    headers = curl_slist_append(headers, accept.c_str());
    std::string content("Content-Type: ");
    content.append(contentType);
    headers = curl_slist_append(headers, content.c_str());
    // set set of headers
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    // Set body reader
    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    
    // Perform the request, res will get the return code
    res = curl_easy_perform(curl);
    long http_code = 0;
    // Check for errors
    if(res != CURLE_OK)
        std::cerr << "curl_easy_perform() failed: "<< curl_easy_strerror(res);
    else{
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    }
    // Clean curl
    curl_easy_cleanup(curl);

    // set return data
    response.setData(http_code, readBuffer);
    return response;
}

HttpResponse Communication::getServer(std::string resource)
{
    // return variable
    HttpResponse response;
    
    // Init curl
    curl = curl_easy_init();
    if(!curl) // If fails, return
        return response;

    // Set full path
    std::string path(serverURL_);
    path.append(resource);
    // Set curl complete url
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    // example.com is redirected, so we tell libcurl to follow redirection
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Perform the request, res will get the return code
    res = curl_easy_perform(curl);
    long http_code = 0;
    // Check for errors
    if(res != CURLE_OK)
        std::cerr << "curl_easy_perform() failed: "<< curl_easy_strerror(res);
    else{
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    }
    // Clean curl
    curl_easy_cleanup(curl);
    
    // set return data
    response.setData(http_code, "");
    return response;
}


//Setters
void Communication::setPeerIPv4Address(std::string IPv4Address) { this->peerIPv4Address_ = IPv4Address; }
void Communication::setPeerIPv6Address(std::string IPv6Address) { this->peerIPv6Address_ = IPv6Address; }

// Private Functions

// Function call for retrieving the body of the request
size_t Communication::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
