cmake_minimum_required(VERSION 3.26)
project(ServerSiryogiAndVityi)

set(CMAKE_CXX_STANDARD 20)
set(DIST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dist)
set(EXECUTABLE_OUTPUT_PATH ${DIST_DIR} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${DIST_DIR} CACHE PATH "Build directory" FORCE)

set(STATIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/static)
set(TEMPLATES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/templates)

if (EXISTS ${STATIC_DIR})
    file(COPY ${STATIC_DIR} DESTINATION ${DIST_DIR})
endif ()

if (EXISTS ${TEMPLATES_DIR})
    file(COPY ${TEMPLATES_DIR} DESTINATION ${DIST_DIR})
endif ()

add_executable(
        ServerSiryogiAndVityi
        main/main.cpp

        WebServer/App/App.cpp
        WebServer/App/App.h
        WebServer/Socket/Socket.cpp
        WebServer/Socket/Socket.h
        WebServer/HttpRequest/HttpRequest.cpp
        WebServer/HttpRequest/HttpRequest.h
        WebServer/Responses/Response/Response.cpp
        WebServer/Responses/Response/Response.h
        WebServer/HttpStatusCodes/HttpStatusCodes.h
        WebServer/Enums/HttpStatus.h
        WebServer/Enums/HttpMethods.h
        WebServer/Enums/HttpVersions.h
        WebServer/Enums/HttpVersions.cpp
        WebServer/Enums/HttpMethods.cpp
        WebServer/Responses/StaticResponse/StaticResponse.cpp
        WebServer/Responses/StaticResponse/StaticResponse.h
        WebServer/Responses/HTMLResponse/HTMLResponse.cpp
        WebServer/Responses/HTMLResponse/HTMLResponse.h
        WebServer/Router/Router.cpp
        WebServer/Router/Router.h
)

if(WIN32)
    target_link_libraries(ServerSiryogiAndVityi wsock32 ws2_32)
endif()
