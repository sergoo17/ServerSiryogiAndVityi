#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <functional>
#include "../HttpRequest/HttpRequest.h"

class Router {
public:
    struct Route {
        std::string path;
        std::function<std::string(HttpRequest)> view;
    };
    std::vector<Route> routers {};
    void add_route(const std::string& path, std::function<std::string(HttpRequest)> view);
};


#endif //ROUTER_H
