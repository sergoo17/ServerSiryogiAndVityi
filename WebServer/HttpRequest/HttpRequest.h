#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>


class HttpRequest {
public:
    std::string _request;
    HttpRequest(const char* request) {
        this->_request = request;
    }
    void parseRequest() {
        size_t posRequest = _request.find("\r\n");
        if (posRequest == std::string::npos) {
            throw; // Invalid request
        }
        std::string RequestLine = _request.substr(0, posRequest);
        std::string HeadersLines = _request.substr(posRequest + 1);

        parseRequestLine(RequestLine);
        parseHeadersLines(HeadersLines);
    }

    void parseRequestLine(std::string request) {
        request.find(' ');
    }
    void parseHeadersLines(std::string request) {

    }
};


#endif //HTTP_REQUEST_H
