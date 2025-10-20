# C++ Web Server

This project is a simple, yet functional, HTTP web server built in C++. It is designed to serve static files and handle basic API routes. The server is built using the lightweight, header-only `cpp-httplib` library and uses CMake for cross-platform compilation.

## Features

*   **Static File Serving**: Serves files from a designated `static` directory, automatically handling common MIME types.
*   **API Routing**: Implements basic API endpoints to handle `GET` requests.
*   **Cross-Platform**: Uses CMake to manage the build process, ensuring it can be compiled on Linux, macOS, and Windows.
*   **Minimal Dependencies**: Relies on the single-header `cpp-httplib` library, making setup and compilation straightforward.
*   **HTTPS Ready**: Includes the necessary preprocessor directive and link dependencies for enabling HTTPS with OpenSSL.

## Project Structure

The project is organized into the following directory structure for clarity and maintainability:

```
Web-Server/
├── CMakeLists.txt
├── include/
│   └── httplib.h
├── src/
│   └── main.cpp
└── static/
    └── index.html
```

*   `/src/`: Contains the main C++ source code for the server.
*   `/include/`: Contains the `cpp-httplib` header file.
*   `/static/`: The root directory for all static assets (HTML, CSS, JavaScript, images) to be served.
*   `CMakeLists.txt`: The build script for CMake.

## Prerequisites

Before you begin, ensure you have the following installed:
*   A C++17 compliant compiler (like GCC, Clang, or MSVC)
*   CMake (version 3.15 or higher)
*   OpenSSL development libraries (for HTTPS support)
*   Boost development libraries (required for more advanced server features, though not strictly for this basic example)

On a Debian-based system (like Ubuntu), you can install the necessary libraries with:
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev libboost-system-dev libboost-thread-dev
```

## Build and Run

Follow these steps to build and run the server from the project's root directory:

1.  **Create a build directory:**
    This keeps the build artifacts separate from the source code.
    ```bash
    mkdir build
    ```

2.  **Navigate into the build directory:**
    ```bash
    cd build
    ```

3.  **Run CMake to configure the project:**
    CMake will find the necessary libraries and generate the `Makefile`.
    ```bash
    cmake..
    ```

4.  **Compile the project using Make:**
    This will compile the source code and create the executable.
    ```bash
    make
    ```

5.  **Run the server:**
    The executable will be created inside the `build` directory.
    ```bash
   ./web_server
    ```

The server will start and listen for connections on `http://localhost:8080`.

## Usage

Once the server is running, you can interact
