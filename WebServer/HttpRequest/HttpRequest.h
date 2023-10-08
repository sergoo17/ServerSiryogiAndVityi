#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <iostream>
#include <map>


class HttpRequest {
public:
    std::string method;
    std::string path;
    std::string httpProtocol;
    std::map<std::string, std::string> headers;
    std::string escapeSymbols = "\r\n";

    explicit HttpRequest(const char* request);
private:
    void parseRequest(const std::string& request);
    void parseRequestLine(const std::string& request);
    void parseHeadersLines(const std::string& request);
};


#endif //HTTP_REQUEST_H
