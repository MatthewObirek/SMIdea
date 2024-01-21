#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include <httplib.h>
#include <libpq-fe.h>
#include <Post.hpp>
#include <User.hpp>

#include "PQWrapper.hpp"

std::vector<std::string> userList;



void runHTTPserver() {
    httplib::Server svr;

    svr.Get("/api/hello", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello, nerd!", "text/plain");
        std::string str = "";
        for (const auto& result : userList) {
            str.append(result.c_str()).append("        ");
        }
        res.set_content(str, "text/plain");

    });

    // std::cout << "hullo?" << std::endl;
    // Add more endpoints as needed

    svr.listen("0.0.0.0", 8080);  // Listen on all available interfaces on port 8080

}


int databaseTestOps() {


    // Connection parameters
    const char *conninfo = "dbname=postgres user=postgres password=postgres123 host=postgres_db port=5432";
    PQWrapper connection(conninfo);

    
    // Establish a connection to the database
    PGconn *conn = PQconnectdb(conninfo);

    // Used to makesure the tables are up to spec
    connection.Query("DROP TABLE IF EXISTS users CASCADE;");
    connection.Query("DROP TABLE IF EXISTS posts;");

    
    PGresult *res = connection.Query("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'users';");
    if (PQntuples(res) > 0) 
    {
        std::cout << "LOG: "<< PQgetvalue(res, 0, 0) << " EXISTS" << std::endl; 
    }
    else 
    {
        std::cout << "LOG: Error: Table not found, [running basic script, replace with other later]" << std::endl; 
        PQclear(connection.Query("DROP TABLE IF EXISTS users;"));
        PQclear(connection.Query("CREATE TABLE users ( uId SERIAL PRIMARY KEY, name VARCHAR(255) UNIQUE, age INT);"));
        PQclear(connection.Query("INSERT INTO users (name, age) VALUES ('bob69', 20), ('zoe420', 30);"));

    }
    PQclear(res);
    res = connection.Query("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'posts';");
    if (PQntuples(res) > 0) 
    {
        std::cout << "LOG: "<< PQgetvalue(res, 0, 0) << " EXISTS" << std::endl; 
    }
    else 
    {
        std::cout << "LOG: Error: Table not found, [running basic script, replace with other later]" << std::endl; 
        PQclear(connection.Query("DROP TABLE IF EXISTS posts;"));
        PQclear(connection.Query("CREATE TABLE posts (pId SERIAL PRIMARY KEY, uName VARCHAR(255) REFERENCES users(name),content TEXT);"));
        PQclear(connection.Query("INSERT INTO posts (uName, content) VALUES ('bob69', 'Gary is a weirdo'), ('zoe420', 'you said it bob');"));

    }
    PQclear(res);

    PGresult *users = connection.Query("SELECT * FROM users");
    int rows1 = PQntuples(users);
    for (int i = 0; i < rows1; ++i) {
        User value(atoi(PQgetvalue(users, i, 0)), PQgetvalue(users, i, 1), atoi(PQgetvalue(users, i, 2)));
        std::cout << "LOG1: "<< value.toString() << std::endl;
        userList.push_back(value.toString());
        
    }


    PQclear(users);
    PQfinish(conn);

    return 0;
}

int main () {
    
    std::cout << "LOG: Backend server is live!" << std::endl;
    

    // Start HTTP server in a separate thread
    std::thread httpServerThread(runHTTPserver);

    // Run database operations in the main thread
    databaseTestOps();

    // Wait for the HTTP server thread to finish
    httpServerThread.join();

    return 0;
}
