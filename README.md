# Simple C++ Web Server

This is a basic C++ web server that serves a login page and authenticates users against an SQLite database. It's multithreaded to handle multiple client connections simultaneously.

## Features

* **HTTP Server**: Handles `GET` and `POST` requests.
* **Web Page**: Serves a `login.html` page for the root (`/`) route.
* **Authentication**: Manages a `users.db` SQLite database for user storage.
* **Login**: Authenticates users via a `POST` request to the `/login` route.
* **Multithreaded**: Uses `std::thread` to manage each client connection separately.
* **Default User**: The database is initialized with a default user:
    * **Username**: `admin`
    * **Password**: `password`

## Dependencies

To build and run this project, you will need:
* **CMake** (version 3.20 or higher)
* **A C++11 compatible compiler** (e.g., g++, clang)
* **SQLite3** (development libraries)
* **pthreads** (POSIX threads library)

On a Debian-based system (like Ubuntu), you can install the dependencies with:
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsqlite3-dev
```

## How to Build and Run

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-url>
    cd <your-repo-directory>
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```

4.  **Compile the project:**
    ```bash
    make
    ```

5.  **Run the server:**
    The executable `WebServer` will be created in the `build` directory.
    ```bash
    ./WebServer
    ```
    The server will start listening on port 8080.

6.  **Access the server:**
    Open your web browser and navigate to `http://localhost:8080`. You should see the login page.

## Project Files

* `server.cpp`: The main server logic, handles sockets and HTTP request parsing.
* `database.cpp`: Functions for initializing and querying the SQLite database.
* `database.h`: Header file for database functions.
* `login.html`: The HTML, CSS, and JS for the login page.
* `CMakeLists.txt`: The build script for CMake.
* `users.db`: The SQLite database file.
