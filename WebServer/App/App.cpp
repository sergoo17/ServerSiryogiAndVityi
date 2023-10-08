#include <iostream>
#include "App.h"
#include "../HttpRequest/HttpRequest.h"
#include "../HttpResponse/HttpResponse.h"

App::App(const char* host, unsigned short port) {
    this->socket = new Socket(host, port);
}

std::string App::newHttpRequest(const char *request) {
    HttpRequest httpRequest(request);
    if (httpRequest.path == "/" and httpRequest.method == "GET") {
        HttpResponse response("", HttpStatus::MethodNotAllowed);
        return response.buildResponse("1");
    }
    return request;
}

void App::run() const {
    socket->listener(newHttpRequest);
}
