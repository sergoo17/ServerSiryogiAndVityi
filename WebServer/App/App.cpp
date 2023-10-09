#include <iostream>
#include "App.h"
#include "../HttpRequest/HttpRequest.h"
#include "../HttpResponse/HttpResponse.h"

App::App(const char* host, unsigned short port) {
    this->socket = new Socket(host, port);
}

std::string App::newHttpRequest(const char *request) {
    HttpRequest httpRequest(request);
    if (httpRequest.path == "/" && httpRequest.method == "GET") {
        return HttpResponse::build("sjhjfsdf", HttpStatus::MethodNotAllowed);
    } else if (httpRequest.path == "/about" && httpRequest.method == "GET") {
        return HttpResponse::build("its me", HttpStatus::MethodNotAllowed);
    }
    return request;
}

void App::run() const {
    socket->listener(newHttpRequest);
}
