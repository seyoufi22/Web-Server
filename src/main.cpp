#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    // Serve files from the "./static" directory.
    auto ret = svr.set_base_dir("./static");
    if (!ret) {
        std::cerr << "The specified base directory doesn't exist..." << std::endl;
        return 1;
    }

    // FIX: Added the required capture clause to the lambda function.
    svr.Get("/hi",(const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello from C++!", "text/plain");
    });

    std::cout << "Server starting at http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}
