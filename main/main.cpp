#include <iostream>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include "../WebServer/App/App.h"

using namespace std;

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

void sendFile(SOCKET clientSocket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string responseHeader = "HTTP/1.1 200 OK\r\nContent-Length: ";
    file.seekg(0, std::ios::end);
    responseHeader += std::to_string(file.tellg());
    responseHeader += "\r\n\r\n";
    send(clientSocket, responseHeader.c_str(), (int)responseHeader.length(), 0);

    file.seekg(0, std::ios::beg);
    char buffer[1024];
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        send(clientSocket, buffer, (int)file.gcount(), 0);
    }

    file.close();
}

[[noreturn]] int handle_socket(){
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if(WSAStartup(DLLVersion, &wsaData) != 0) {
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    while (true) {
        SOCKET newConnection;
        newConnection = accept(sListen, (SOCKADDR *) &addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error #2\n";
        } else {
            std::cout << "Client Connected!\n";

            const int BUFFER_SIZE = 4096;
            char buffer[BUFFER_SIZE] = {0};
            int bytesReceived = recv(newConnection, buffer, BUFFER_SIZE, 0);
            if (bytesReceived < 0) {
                std::cout << "------ Failed to receive bytes from client socket connection ------\n\n";
            }

            std::cout << buffer << endl;

            std::string request(buffer);
            size_t start = request.find("GET ") + 4;
            size_t end = request.find(" HTTP");
            std::string requestedFile = request.substr(start, end - start);

            // Construct the full path to the requested file
            std::string filePath = "../static/html" + requestedFile;
            cout << filePath << endl;

            // Check if the requested file exists
            std::ifstream fileCheck(filePath);
            if (fileCheck.good()) {
                // Send the requested static file
                sendFile(newConnection, filePath);
            } else {
                ostringstream response;
                response << "HTTP/1.1 200 OK\r\n";
                response << "Content-Type: text/html\r\n";
                response << "\r\n";
                response << "<h1>sdf</h1>";
                string responseString = response.str();

                int bytesSent;
                long totalBytesSent = 0;

                while (totalBytesSent < responseString.size()) {
                    bytesSent = send(newConnection, responseString.c_str(), (int)responseString.size(), 0);
                    if (bytesSent < 0) {
                        break;
                    }
                    totalBytesSent += bytesSent;
                }

                if (totalBytesSent == responseString.size()) {
                    std::cout << "------ Server Response sent to client ------\n\n";
                }
                else {
                    std::cout << "Error sending response to client.";
                }
            }

            closesocket(newConnection);
        }
    }
}
std::string main_html() {
    1+1;
    return "sdfdsfsdf";
}
int main() {
    App app("127.0.0.1", 8888);
    app.add_view("/", main_html);
    app.run();
//    char tmp[256];
//    getcwd(tmp, 256);
//    cout << "Current working directory: " << tmp << endl;
//    handle_socket();
}