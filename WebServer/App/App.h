#ifndef APP_H
#define APP_H

#include "../Socket/Socket.h"
#include "../HttpRequest/HttpRequest.h"
#include "../Router/Router.h"
#include <filesystem>
#include <map>

class App {
public:
    std::string staticDir = "static";
    std::string templatesDir = "templates";
    App(const char* host, unsigned short port);
    void run();
    Router router;
private:
    Socket *socket;

    std::filesystem::path templatesPath;
    std::filesystem::path staticPath;
    static std::string newHttpRequest(const char * request, Router & router);
    static std::string getProjectDirectory();
    static std::filesystem::path getPath(const std::string& directory);
};

#endif //APP_H