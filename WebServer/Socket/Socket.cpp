#include <iostream>
#include "Socket.h"
#include <functional>

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
    WORD DLLVersion = MAKEWORD(2, 2);
    int result = WSAStartup(DLLVersion, &wsaData);
    if(result != 0) {
        throw std::logic_error("WSAStartup not init");
    }
    setInfo();
    createSocket();
    bindSocket();
    listenSocket();
}

void Socket::setInfo() {
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int result = getaddrinfo(host, std::to_string(port).c_str(), &hints, &addrResult);
    if (result != 0) {
        finish();
        throw std::logic_error("getaddrinfo failed");
    }
}

void Socket::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket <= 0) {
        throw std::logic_error("Socket creating failed");
    }
}

void Socket::bindSocket() {
    int result = bind(serverSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
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
    freeaddrinfo(addrResult);
}

void Socket::finish() {
    closeSocket();
    WSACleanup();
}

[[noreturn]] void Socket::listener(const std::function<std::string(const char*)>& callback) const {
    while (true) {
        sockaddr_in clientAddr{};
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

        char clientIP[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN) == nullptr) {
            std::cerr << "inet_ntop failed." << std::endl;
        } else {
            std::cout << "Client connected from IP address: " << clientIP << std::endl;
        }
        if (clientSocket != 0) {
            const int BUFFER_SIZE = 2048;
            char buffer[BUFFER_SIZE] = {0};
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived < 0) {
                std::cout << "------ Failed to receive bytes from client socket connection ------\n";
                continue;
            }
            std::string sendBuffer = callback(buffer);
            send(clientSocket, sendBuffer.c_str(), (int)sendBuffer.size(), 0);
            closesocket(clientSocket);
        } else {
            std::cout << "------ Error client connected ------\n\n";
        }
    }
}

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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

[[noreturn]] Socket::listener(const std::function<const char*(const char*)>& callback) {
    while (true) {
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection" << std::endl;
        }
    }
}

#endif