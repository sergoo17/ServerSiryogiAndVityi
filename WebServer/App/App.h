#ifndef APP_H
#define APP_H

#include "../Socket/Socket.h"
#include "../HttpRequest/HttpRequest.h"
#include <filesystem>
#include <map>

class App {
public:
    std::string staticDir = "static";
    std::string templatesDir = "templates";
    App(const char* host, unsigned short port);
    void run();
    void add_route(const std::string& path, std::function<std::string(HttpRequest)> view);
private:
    Socket *socket;
    struct Route {
        std::string path;
        std::function<std::string(HttpRequest)> view;
    };
    static std::vector<Route> routers;
    std::filesystem::path templatesPath;
    std::filesystem::path staticPath;
    static std::string newHttpRequest(const char * request);
    static std::string getProjectDirectory();
    static std::filesystem::path getPath(const std::string& directory);
};

#endif //APP_H