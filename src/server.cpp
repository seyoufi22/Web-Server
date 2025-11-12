#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "database.h"

using namespace std;
const int PORT = 8080;
const int BUFFER_SIZE = 1024;

//handle individual client connections
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    string request(buffer);
    stringstream ss(request);
    string method, path, http_version;
    ss >> method >> path >> http_version;
    
    string response, content;

    if (method == "GET" && path == "/") {
        // Serve the login page
        ifstream file("/home/ahmed/WebServer/data/login.html");
        if (file) {
            stringstream file_buffer;
            file_buffer << file.rdbuf();
            content = file_buffer.str();
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
        } else {
            // If the file can't be opened, send a specific 404 error
            content = "<h1>404 Not Found</h1><p>login.html not found.</p>";
            response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
        }
    } else if (method == "POST" && path == "/login") {
        // Handle login form submission
        string body = request.substr(request.find("\r\n\r\n") + 4);

        // Very simple URL decoding for form data
        size_t user_pos = body.find("username=") + 9;
        size_t pass_pos = body.find("&password=") + 10;
        string username = body.substr(user_pos, pass_pos - user_pos - 10);
        string password = body.substr(pass_pos);

        if (authenticate_user(username, password)) {
            content = "<h1>Login Successful</h1>";
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
        } else {
            content = "<h1>Invalid Credentials</h1>";
            response = "HTTP/1.1 401 Unauthorized\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
        }
    } else {
        content = "<h1>404 Not Found</h1><p>The requested resource was not found on this server.</p>";
        response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}

int main() {
    init_database();
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue; // Continue to the next iteration
        }

        // Create a new thread to handle the client
        thread client_thread(handle_client, new_socket);
        client_thread.detach(); // run independently
    }

    return 0;
}

