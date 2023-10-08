#include <iostream>
#include <string>
#include <boost/asio.hpp>
//FDSFDSFSDFDSF


using namespace std;
using namespace boost::asio;
using ip::tcp;

const string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";

int main() {
    io_service io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));

    while (true) {
        tcp::socket socket(io);
        acceptor.accept(socket);

        // Read request
        char data[1024];
        socket.read_some(buffer(data));

        // Send response
        write(socket, buffer(response));
    }

    return 0;
}
