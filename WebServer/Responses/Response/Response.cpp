#include "Response.h"
#include "../../HttpStatusCodes/HttpStatusCodes.h"

namespace Response {
    HttpVersion defaultHttpProtocol = HttpVersion::HTTP_1_1;
    HttpStatus defaultStatusCode = HttpStatus::OK;
}

std::string Response::build(const std::string& content, HttpStatus statusCode, HttpVersion httpVersion) {
    return _build(content, statusCode, httpVersion);
}

std::string Response::build(const std::string& content, HttpVersion httpVersion) {
    return _build(content, defaultStatusCode, httpVersion);
}

std::string Response::build(const std::string& content,  HttpStatus statusCode) {
    return _build(content, statusCode, defaultHttpProtocol);
}

std::string Response::build(const std::string& content) {
    return _build(content, defaultStatusCode, defaultHttpProtocol);
}

std::string Response::_build(const std::string& content, HttpStatus statusCode, HttpVersion httpVersion) {
    std::string response;
    std::string httpProtocol = getStringHttpVersions(httpVersion);
    std::string statusDetail = HttpStatusCodes::reasonPhrase(statusCode);
    response = httpProtocol + " " + std::to_string(statusCode) + " " + statusDetail + "\r\n";
    response += "\r\n";
    response += content;
    return response;
}
