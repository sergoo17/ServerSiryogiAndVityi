#include <iostream>
#include "App.h"
#include "../HttpRequest/HttpRequest.h"

App::App(const char* host, unsigned short port) {
    this->socket = new Socket(host, port);
}

const char * App::newHttpRequest(const char *request) {
    HttpRequest httpRequest(request);
    httpRequest.parseRequest();
    return request;
}

void App::run() const {
    socket->listener(newHttpRequest);
}
