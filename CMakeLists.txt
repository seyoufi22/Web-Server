cmake_minimum_required(VERSION 3.15)
project(Web-Server VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71.0 REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(web_server src/main.cpp)

target_include_directories(web_server PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(web_server PRIVATE
    Boost::system
    Threads::Threads
    OpenSSL::SSL
    OpenSSL::Crypto
)
