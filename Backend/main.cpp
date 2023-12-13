#include <iostream>
#include <thread>

#include <httplib.h>
#include <libpq-fe.h>


void runHTTPserver() {
    httplib::Server svr;

    svr.Get("/api/hello", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello, nerd!", "text/plain");
    });

    // Add more endpoints as needed

    svr.listen("0.0.0.0", 8080);  // Listen on all available interfaces on port 8080

}

void Query(PGconn *conn, const char *query) {
    std::cout << query << std::endl;
    PGresult *response = PQexec(conn, query);

    if (PQresultStatus(response) != PGRES_TUPLES_OK) {
        std::cerr << "Query execution failed: " << PQresultErrorMessage(response) << std::endl;
        PQclear(response);
        PQfinish(conn);
        return;
    }

    // Print the query result
    int rows1 = PQntuples(response);
    int cols1 = PQnfields(response);
    std::cout << "Rows: " << rows1 << ", Cols: " << cols1 << std::endl; 
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            const char *value = PQgetvalue(response, i, j);
            std::cout << "PSQL: " << value << "\t";
        }
    
        std::cout << std::endl;
    }
    PQclear(response);
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
    
    Query(conn, "SELECT current_database()");

    Query(conn, "SELECT datname FROM pg_database");

    Query(conn, "SELECT table_name FROM information_schema.tables");

    Query(conn, "SELECT * FROM postgres");

    /*
    const char *list = "SELECT datname FROM pg_database";
    PGresult *check = PQexec(conn, list);

    if (PQresultStatus(check) != PGRES_TUPLES_OK) {
        std::cerr << "Query execution failed: " << PQresultErrorMessage(check) << std::endl;
        PQclear(check);
        PQfinish(conn);
        return 1;
    }

    // Print the query result
    int rows1 = PQntuples(check);
    int cols1 = PQnfields(check);

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            const char *value = PQgetvalue(check, i, j);
            std::cout << "PSQL: " << value << "\t";
        }
        std::cout << std::endl;
    }
    const char *db = "USE pg_database";
    PGresult *dbs = PQexec(conn, db);

    // Perform a simple SELECT query
    const char *query = "SELECT * FROM postgres";
    PGresult *res = PQexec(conn, query);

    // Check if the query was successful
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "SELECT query failed: " << PQresultErrorMessage(res) << std::endl;
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    // Print the results of the SELECT query
    int rows = PQntuples(res);
    int cols = PQnfields(res);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << PQgetvalue(res, i, j) << "\t";
        }
        std::cout << std::endl;
    }

    // Perform a simple INSERT query
    const char *insertQuery = "INSERT INTO your_table_name(column1, column2) VALUES('value1', 'value2')";
    PGresult *insertRes = PQexec(conn, insertQuery);

    // Check if the INSERT query was successful
    if (PQresultStatus(insertRes) != PGRES_COMMAND_OK) {
        std::cerr << "INSERT query failed: " << PQresultErrorMessage(insertRes) << std::endl;
        PQclear(insertRes);
    } else {
        std::cout << "INSERT query successful!" << std::endl;
        PQclear(insertRes);
    }
    //*/
    // Release the results and close the connection
    // PQclear(res);
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
