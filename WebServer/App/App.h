#ifndef APP_H
#define APP_H

#include "../Socket/Socket.h"

class App {
public:
    App(const char* host, unsigned short port);
    Socket *socket;
    void run() const;
    static const char * newHttpRequest(const char * request);
};

#endif //APP_H