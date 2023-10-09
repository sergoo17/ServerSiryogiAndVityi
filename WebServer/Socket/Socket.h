#ifndef SOCKET_H
#define SOCKET_H

#include <functional>
#include <string>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#define WIN32_LEAN_AND_MEAN

class Socket {
public:
    const char* host;
    unsigned short port;
    Socket(const char *host, unsigned short port);
    ~Socket();

    [[noreturn]] void listener(const std::function<std::string(const char*)>& callback) const;
private:
    SOCKET serverSocket{};
    ADDRINFO hints{};
    ADDRINFO *addrResult{};
    void init();
    void createSocket() ;
    void bindSocket() ;
    void listenSocket() const ;
    void setInfo();
    void closeSocket() const ;
    void finish();
};

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Socket {
public:
    const char* host;
    unsigned short port;
    Socket(const char *host, unsigned short port);
    ~Socket();
    void listener(const std::function<const char*(const char*)>& callback);
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
};

#endif

#endif //SOCKET_H