#include "HttpMethods.h"

std::string getStringHttpMethod(HttpMethods method) {
    switch (method) {
        case HttpMethods::GET:
            return "GET";
        case HttpMethods::POST:
            return "POST";
        case HttpMethods::PUT:
            return "PUT";
        case HttpMethods::DELETE_:
            return "DELETE";
        case HttpMethods::PATCH:
            return "PATCH";
        case HttpMethods::HEAD:
            return "HEAD";
        case HttpMethods::OPTIONS:
            return "OPTIONS";
        case HttpMethods::TRACE:
            return "TRACE";
        case HttpMethods::CONNECT:
            return "CONNECT";
        case HttpMethods::INVALID:
            return "INVALID";
        default:
            return "";
    }
}