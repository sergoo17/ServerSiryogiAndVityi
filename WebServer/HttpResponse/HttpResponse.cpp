#include "HttpResponse.h"
#include "../HttpStatusCodes/HttpStatusCodes.h"

HttpResponse::HttpResponse(const char* content, HttpMethods method, HttpStatus statusCode, HttpVersion httpProtocol) {
    _method = method;
    _statusCode = statusCode;
    _httpProtocol = httpProtocol;
    buildResponse(content);
}

HttpResponse::HttpResponse(const char* content, HttpMethods method, HttpVersion httpProtocol) {
    _method = method;
    _httpProtocol = httpProtocol;
    buildResponse(content);
}

HttpResponse::HttpResponse(const char* content, HttpMethods method, HttpStatus statusCode) {
    _method = method;
    _statusCode = statusCode;
    buildResponse(content);
}

HttpResponse::HttpResponse(const char* content, HttpMethods method) {
    _method = method;
    buildResponse(content);
}

HttpResponse::HttpResponse(const char* content, HttpStatus statusCode) {
    _statusCode = statusCode;
    buildResponse(content);
}

HttpResponse::HttpResponse(const char* content) {
    buildResponse(content);
}

std::string HttpResponse::buildResponse(const char* content) {
    std::string response;
    std::string httpProtocol = getStringHttpVersions(_httpProtocol);
    std::string statusDetail = HttpStatusCodes::reasonPhrase(_statusCode);
    response = httpProtocol + " " + std::to_string(_statusCode) + " " + statusDetail + "\r\n";
    response += "\r\n";
    response += content;
    return response;
}
