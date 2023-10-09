#include <iostream>
#include <fstream>
#include <utility>
#include "App.h"
#include "../HttpRequest/HttpRequest.h"
#include "../Responses/Response/Response.h"
#include "../Responses/HTMLResponse/HTMLResponse.h"

App::App(const char* host, unsigned short port) {
    this->socket = new Socket(host, port);
}

std::string App::newHttpRequest(const char *request) {
    HttpRequest httpRequest(request);

    if (httpRequest.path.starts_with("/static/")) {
        return Response::build("<img src='/static/images/image.png' alt='hi'>");
    }
    else {
        for(const auto& route: routers) {
            if (httpRequest.path == route.path) {
                return route.view(httpRequest);
            }
        }
    }
    return HTMLResponse::build("404.html");
}

void App::run() {
    staticPath = getPath(staticDir);
    templatesPath = getPath(templatesDir);
    socket->listener(newHttpRequest);
}

std::string App::getProjectDirectory() {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
    if (projectDirectory == "cmake-build-debug") return projectDirectory.parent_path().string();
    else return projectDirectory.string();
}

std::filesystem::path App::getPath(const std::string& directory) {
    std::filesystem::path templatesPath = std::filesystem::path(getProjectDirectory()) / directory;
    if (!std::filesystem::exists(templatesPath)) {
        std::filesystem::create_directory(templatesPath);
    }
    return templatesPath;
}

void App::add_route(const std::string& path, std::function<std::string(HttpRequest)> view) {
    Route route;
    route.path = path;
    route.view = std::move(view);
    routers.push_back(route);
}
