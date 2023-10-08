#ifndef HTTP_METHODS_H
#define HTTP_METHODS_H

#include <string>

enum class HttpMethods {
    GET,
    POST,
    PUT,
    DELETE_,
    PATCH,
    HEAD,
    OPTIONS,
    TRACE,
    CONNECT,
    INVALID
};

std::string getStringHttpMethod(HttpMethods method);

#endif //HTTP_METHODS_H
