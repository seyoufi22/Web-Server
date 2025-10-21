cmake_minimum_required(VERSION 3.20)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

# Copy data files to the build directory so the executable can find them.
# This ensures that login.html and users.db are in the same
# directory as the final "WebServer" executable.
file(COPY
    "data/login.html"
    "data/users.db"
    DESTINATION ${CMAKE_BINARY_DIR}
)

add_executable(WebServer src/server.cpp src/database.cpp)

target_include_directories(WebServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(WebServer sqlite3 pthread)
