#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "../Enums/HttpMethods.h"
#include "../Enums/HttpStatus.h"
#include "../Enums/HttpVersions.h"

class HttpResponse {
public:
    HttpResponse(const char* content, HttpMethods method, HttpStatus statusCode, HttpVersion httpProtocol);
    HttpResponse(const char* content, HttpMethods method, HttpVersion httpProtocol);
    HttpResponse(const char* content, HttpMethods method, HttpStatus statusCode);
    HttpResponse(const char* content, HttpMethods method);
    HttpResponse(const char* content, HttpStatus statusCode);
    explicit HttpResponse(const char* content);
    std::string buildResponse(const char* content);
private:
    HttpVersion _httpProtocol = HttpVersion::HTTP_1_1;
    HttpMethods _method = HttpMethods::GET;
    HttpStatus _statusCode = HttpStatus::OK;
};

#endif //HTTP_RESPONSE_H
