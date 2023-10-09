#include "HttpResponse.h"
#include "../HttpStatusCodes/HttpStatusCodes.h"

namespace HttpResponse {
    HttpVersion defaultHttpProtocol = HttpVersion::HTTP_1_1;
    HttpStatus defaultStatusCode = HttpStatus::OK;
}

std::string HttpResponse::build(const char* content, HttpStatus statusCode, HttpVersion httpVersion) {
    return _build(content, statusCode, httpVersion);
}

std::string HttpResponse::build(const char* content, HttpVersion httpVersion) {
    return _build(content, defaultStatusCode, httpVersion);
}

std::string HttpResponse::build(const char* content,  HttpStatus statusCode) {
    return _build(content, statusCode, defaultHttpProtocol);
}

std::string HttpResponse::build(const char* content) {
    return _build(content, defaultStatusCode, defaultHttpProtocol);
}

std::string HttpResponse::_build(const char* content, HttpStatus statusCode, HttpVersion httpVersion) {
    std::string response;
    std::string httpProtocol = getStringHttpVersions(httpVersion);
    std::string statusDetail = HttpStatusCodes::reasonPhrase(statusCode);
    response = httpProtocol + " " + std::to_string(statusCode) + " " + statusDetail + "\r\n";
    response += "\r\n";
    response += content;
    return response;
}
