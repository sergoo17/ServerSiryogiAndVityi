#include "../WebServer/App/App.h"

//void sendFile(SOCKET clientSocket, const std::string& filePath) {
//    std::ifstream file(filePath, std::ios::in | std::ios::binary);
//    if (!file) {
//        std::cerr << "Error opening file: " << filePath << std::endl;
//        return;
//    }
//
//    std::string responseHeader = "HTTP/1.1 200 OK\r\nContent-Length: ";
//    file.seekg(0, std::ios::end);
//    responseHeader += std::to_string(file.tellg());
//    responseHeader += "\r\n\r\n";
//    send(clientSocket, responseHeader.c_str(), (int)responseHeader.length(), 0);
//
//    file.seekg(0, std::ios::beg);
//    char buffer[1024];
//    while (!file.eof()) {
//        file.read(buffer, sizeof(buffer));
//        send(clientSocket, buffer, (int)file.gcount(), 0);
//    }
//
//    file.close();
//}

int main() {
    App app("127.0.0.1", 8888);
    app.run();
    return 1;
}