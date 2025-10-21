# Specify the minimum version of CMake required.
cmake_minimum_required(VERSION 3.20)

# Define the project name. This will also be the default solution/project name in CLion.
project(WebServer)

# Set the C++ standard to C++11, as required by the source code.
set(CMAKE_CXX_STANDARD 11)

# Tell CMake to create an executable named "WebServer"
# from the following source files.
add_executable(WebServer server.cpp database.cpp)

# This is the most important line for fixing linker errors.
# It tells CMake to link your "WebServer" executable against
# the sqlite3 and pthread (for threading) libraries.
target_link_libraries(WebServer sqlite3 pthread)
