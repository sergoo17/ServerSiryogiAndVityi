#include "HttpRequest.h"

HttpRequest::HttpRequest(const char* request) {
    parseRequest(std::string(request));
}

void HttpRequest::parseRequest(const std::string& request) {
    size_t posRequest = request.find(escapeSymbols);
    if (posRequest == std::string::npos) {
        throw std::logic_error("Invalid Request");
    }
    std::string RequestLine = request.substr(0, posRequest);
    std::string HeadersLines = request.substr(posRequest + escapeSymbols.size());

    parseRequestLine(RequestLine);
    parseHeadersLines(HeadersLines);
}

void HttpRequest::parseRequestLine(const std::string& request) {
    size_t posMethod = request.find(' ');
    size_t posPath = request.rfind(' ');
    if (posMethod != std::string::npos && posPath != std::string::npos) {
        method = request.substr(0, posMethod);
        path = request.substr(posMethod + 1, posPath - posMethod - 1);
        httpProtocol = request.substr(posPath + 1);
    } else {
        throw std::logic_error("Parse Request Section Error");
    }
}

void HttpRequest::parseHeadersLines(const std::string& request) {
    size_t pos = 0;
    while (pos < request.size()) {
        size_t end = request.find("\r\n", pos);
        if (end == std::string::npos) {
            break;
        }

        size_t colon = request.find(':', pos);
        if (colon != std::string::npos && colon < end) {
            std::string key = request.substr(pos, colon - pos);
            std::string value = request.substr(colon + 2, end - colon - 2);
            headers[key] = value;
        }

        pos = end + 2;
    }
}