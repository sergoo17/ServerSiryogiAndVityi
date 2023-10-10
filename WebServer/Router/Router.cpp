#include "Router.h"

void Router::add_route(const std::string &path, std::function<std::string(HttpRequest)> view) {
    Route route;
    route.path = path;
    route.view = std::move(view);
    routers.push_back(route);
}
