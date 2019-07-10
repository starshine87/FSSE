cmake_minimum_required(VERSION 3.14)
project(Demo)

set(CMAKE_CXX_STANDARD 14)

find_package (openssl REQUIRED)

include_directories(src)

add_executable(Demo
        src/add_token.h
        src/client.cpp
        src/client.h
        src/config.hpp
        src/main.cpp
        src/search_token.h
        src/server.cpp
        src/server.h
        src/util.cpp
        src/util.h)

target_link_libraries (Demo OpenSSL::SSL)
