cmake_minimum_required(VERSION 3.26)
project(ServerSiryogiAndVityi)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ServerSiryogiAndVityi
        main/main.cpp
#        WebServer/Sockets/Socket.cpp
#        WebServer/Sockets/Socket.h
        WebServer/App/App.cpp
        WebServer/App/App.h
        WebServer/Socket/Socket.cpp
        WebServer/Socket/Socket.h
        WebServer/HttpRequest/HttpRequest.cpp
        WebServer/HttpRequest/HttpRequest.h
)
#if(WIN32)
#    add_executable(
#            ServerSiryogiAndVityi1
#            WebServer/Sockets/WindowsSocket.cpp
#            WebServer/Sockets/WindowsSocket.h
#
#    )
#else()
#    add_executable(
#            ServerSiryogiAndVityi1
#            WebServer/Sockets/UnixSocket.cpp
#            WebServer/Sockets/UnixSocket.h
#
#    )
#endif()
if(WIN32)
    target_link_libraries(ServerSiryogiAndVityi wsock32 ws2_32)
endif()
