cmake_minimum_required(VERSION 3.26)
project(ServerSiryogiAndVityi)
set(CMAKE_CXX_STANDARD 23)

set(BOOST_ROOT "/usr/include/boost_build")
set(BOOST_INCLUDEDIR "/usr/include/boost_build/include")
set(BOOST_INCLUDE_DIR "/usr/include/boost_build/include")
set(BOOST_LIBRARYDIR "/usr/include/boost_build/lib")
#set(Boost_USE_STATIC_RUNTIME ON)
#set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.83.0 REQUIRED COMPONENTS ALL)

add_executable(ServerSiryogiAndVityi src/server/biba.cpp)

target_include_directories(ServerSiryogiAndVityi PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(ServerSiryogiAndVityi ${Boost_LIBRARIES})