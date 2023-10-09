#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "../Enums/HttpMethods.h"
#include "../Enums/HttpStatus.h"
#include "../Enums/HttpVersions.h"

namespace HttpResponse {
    extern HttpVersion defaultHttpProtocol;
    extern HttpStatus defaultStatusCode;

    std::string build(const char* content, HttpStatus statusCode, HttpVersion httpProtocol);
    std::string build(const char* content, HttpVersion httpProtocol);
    std::string build(const char* content, HttpStatus statusCode);
    std::string build(const char* content);
    std::string _build(const char* content, HttpStatus statusCode, HttpVersion httpProtocol);
}

#endif //HTTP_RESPONSE_H
