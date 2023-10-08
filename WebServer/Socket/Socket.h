#ifndef SOCKET_H
#define SOCKET_H

#ifdef _WIN32

#include <winsock2.h>
#include <functional>

#define WIN32_LEAN_AND_MEAN

class Socket {
public:
    const char* host;
    unsigned short port;
    Socket(const char *host, unsigned short port);
    ~Socket();

    [[noreturn]] void listener(const std::function<const char*(const char*)>& callback);
private:
    SOCKET serverSocket{};
    SOCKADDR_IN addr{};
    int sizeAddr = sizeof(addr);
    void init();
    void createSocket() ;
    void bindSocket() ;
    void listenSocket() const ;
    void setInfo(const char *host, unsigned short port) ;
    void closeSocket() const ;
    void finish();
};

#else

class Socket {
public:
    const char* host;
    unsigned short port;
    Socket(const char *host, unsigned short port);
    ~Socket();
private:
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    void init();
    void createSocket();
    void bindSocket();
    void listenSocket();
    void setInfo(const char *host, unsigned short port);
    void closeSocket();
    void finish();
    void listener();
};

#endif

#endif //SOCKET_H