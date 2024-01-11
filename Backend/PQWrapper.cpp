#include "PQWrapper.hpp"
#include <iostream>

PQWrapper::PQWrapper(const char *connInfo) 
{
    conn = PQconnectdb(connInfo);

    std::cout << "Wrapper LOG: Connection attempted" << std::endl;

    // Check if the connection was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }
    std::cout << "Wrapper LOG: Connection established" << std::endl;
}

PGresult* PQWrapper::Query(const char *query) {
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