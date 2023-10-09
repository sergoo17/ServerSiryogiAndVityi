#ifndef RESPONSE_H
#define RESPONSE_H

#include "../../Enums/HttpMethods.h"
#include "../../Enums/HttpStatus.h"
#include "../../Enums/HttpVersions.h"

namespace Response {
    extern HttpVersion defaultHttpProtocol;
    extern HttpStatus defaultStatusCode;

    std::string build(const std::string&, HttpStatus statusCode, HttpVersion httpProtocol);
    std::string build(const std::string&, HttpVersion httpProtocol);
    std::string build(const std::string&, HttpStatus statusCode);
    std::string build(const std::string& content);
    std::string _build(const std::string& content, HttpStatus statusCode, HttpVersion httpProtocol);
}

#endif //RESPONSE_H
