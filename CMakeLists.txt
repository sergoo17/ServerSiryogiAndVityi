cmake_minimum_required(VERSION 3.26)
project(ServerSiryogiAndVityi)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        ServerSiryogiAndVityi
        main/main.cpp

        WebServer/App/App.cpp
        WebServer/App/App.h
        WebServer/Socket/Socket.cpp
        WebServer/Socket/Socket.h
        WebServer/HttpRequest/HttpRequest.cpp
        WebServer/HttpRequest/HttpRequest.h
        WebServer/HttpResponse/HttpResponse.cpp
        WebServer/HttpResponse/HttpResponse.h
        WebServer/HttpStatusCodes/HttpStatusCodes.h
        WebServer/Enums/HttpStatus.h
        WebServer/Enums/HttpMethods.h
        WebServer/Enums/HttpVersions.h
        WebServer/Enums/HttpVersions.cpp
        WebServer/Enums/HttpMethods.cpp
)

if(WIN32)
    target_link_libraries(ServerSiryogiAndVityi wsock32 ws2_32)
endif()
