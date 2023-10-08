#include <iostream>

#include "Socket.h"

#ifdef _WIN32

#include <winsock2.h>
#include "windows.h"

Socket::Socket(const char *host, unsigned short port) {
    this->host = host;
    this->port = port;
    init();
}

Socket::~Socket() {
    closeSocket();
    WSACleanup();
}

void Socket::init() {
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    int result = WSAStartup(DLLVersion, &wsaData);
    if(result != 0) {
        throw std::logic_error("WSAStartup not init");
    }
    setInfo(host, port);
    createSocket();
    bindSocket();
    listenSocket();
}

void Socket::setInfo(const char *hostname, unsigned short numPort) {
    addr.sin_addr.s_addr = inet_addr(hostname);
    addr.sin_port = htons(numPort);
    addr.sin_family = AF_INET;
}

void Socket::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket <= 0) {
        throw std::logic_error("Socket creating failed");
    }
}

void Socket::bindSocket() {
    int result = bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
    if (result < 0) {
        throw std::logic_error("Socket binding failed");
    }
}

void Socket::listenSocket() const {
    int result = listen(serverSocket, SOMAXCONN);
    if (result < 0) {
        throw std::logic_error("Socket listing failed");
    }
}

void Socket::closeSocket() const {
    closesocket(serverSocket);
}

void Socket::finish() {
    closeSocket();
    WSACleanup();
}

[[noreturn]] void Socket::listener(const std::function<const char*(const char*)>& callback) {
    while (true) {
        int sizeofAddr = sizeof(addr);
        SOCKET clientSocket = accept(serverSocket, (SOCKADDR *) &addr, &sizeofAddr);

        if (clientSocket != 0) {
            const int BUFFER_SIZE = 2048;
            char buffer[BUFFER_SIZE] = {0};
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived < 0) {
                std::cout << "------ Failed to receive bytes from client socket connection ------\n";
                continue;
            }
            const char *sendBuffer = callback(buffer);
            send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
            closesocket(clientSocket);
        } else {
            std::cout << "------ Error client connected ------\n\n";
        }
    }
}

#else

#include <sys/socket.h>
#include <netinet/in.h>

Socket::Socket(const char *host, unsigned short port) {
    this->host = host;
    this->port = port;
    init();
}

Socket::~Socket() {
    finish();
}

void Socket::init() {
    setInfo(host, port);
    createSocket();
    bindSocket();
    listenSocket();
}

void Socket::setInfo(const char *hostname, unsigned short numPort) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(numPort);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
}

void Socket::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}

void Socket::bindSocket() {
    int result = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == 0) {
        throw std::logic_error("Socket binding failed");
    }
}

void Socket::listenSocket() {
    int result = listen(serverSocket, SOMAXCONN);
    if (result == 0) {
        throw std::logic_error("Socket listing failed");
    }
}

void Socket::closeSocket() {
    closesocket(serverSocket);
}

void Socket::finish() {
    closeSocket();
}

void Socket::listener() {
    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection" << std::endl;
            return 1;
        }
    }
}

#endif