#include <httplib.h>

int main () {
    httplib::Server svr;

    svr.Get("/api/hello", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello, World!", "text/plain");
    });

    // Add more endpoints as needed

    svr.listen("0.0.0.0", 8080);  // Listen on all available interfaces on port 8080

    return 0;
}
