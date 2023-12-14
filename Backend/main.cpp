#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include <httplib.h>
#include <libpq-fe.h>

std::vector<std::string> userList;

void runHTTPserver() {
    httplib::Server svr;

    svr.Get("/api/hello", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello, nerd!", "text/plain");

        // for (const auto& result : userList) {
        //     res.set_content(result.c_str(), "text/plain");
        // }
    });

    // std::cout << "hullo?" << std::endl;
    // Add more endpoints as needed

    svr.listen("0.0.0.0", 8080);  // Listen on all available interfaces on port 8080

}

PGresult* Query(PGconn *conn, const char *query) {
    std::cout << "Query:" << std::endl << query << std::endl;
    PGresult *response = PQexec(conn, query);

    if (PQresultStatus(response) != PGRES_COMMAND_OK && PQresultStatus(response) != PGRES_TUPLES_OK) {
        std::cerr << "Query execution failed: " << PQresultErrorMessage(response) << std::endl;
        PQclear(response);
        PQfinish(conn);
        return nullptr;
    }

    // Print the query result
    int rows1 = PQntuples(response);
    int cols1 = PQnfields(response);
    std::cout << "PSQL: " << std::endl; 
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            const char *value = PQgetvalue(response, i, j);
            std::cout << value << "\t";
        }
    
        std::cout << std::endl;
    }
    return response;
}



int databaseTestOps() {

    std::cout << "LOG: Hello, nerd! Test Time" << std::endl;

    // Connection parameters
    const char *conninfo = "dbname=postgres user=postgres password=postgres123 host=postgres_db port=5432";
    
    std::cout << "LOG: " << conninfo << std::endl;

    // Establish a connection to the database
    PGconn *conn = PQconnectdb(conninfo);
    
    std::cout << "LOG: Connection attempted" << std::endl;

    // Check if the connection was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }
    std::cout << "LOG: Connection established" << std::endl;
    

    PGresult *res = Query(conn, "SELECT table_name FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'users';");
    if (PQntuples(res) > 0) 
    {
        std::cout << "LOG: "<< PQgetvalue(res, 0, 0) << " EXISTS" << std::endl; 
    }
    else 
    {
        std::cout << "LOG: Error: Table not found, [running basic script, replace with other later]" << std::endl; 
        PQclear(Query(conn, "DROP TABLE IF EXISTS users;"));
        PQclear(Query(conn, "CREATE TABLE users ( id SERIAL PRIMARY KEY, name VARCHAR(255), age INT);"));
        PQclear(Query(conn, "INSERT INTO users (name, age) VALUES ('bob69', 20), ('zoe420', 30);"));

    }
    PQclear(res);

    PGresult *users = Query(conn, "SELECT * FROM users");
    int rows1 = PQntuples(users);
    int cols1 = PQnfields(users);
    for (int i = 0; i < rows1; ++i) {
        std::string user = "";
        for (int j = 0; j < cols1; ++j) {
            const char *value = PQgetvalue(users, i, j);
            std::cout << value << "\t";
            user.append(value).append("   ");  // Store the result in the global variable
        }
        userList.push_back(user);
        
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
