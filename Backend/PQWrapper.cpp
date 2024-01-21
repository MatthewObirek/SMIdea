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


PGresult* PQWrapper::QueryParams(const char *query, int nParams, const Oid* paramTypes,
                                 const char* const* paramValues, const int* paramLengths,
                                 const int* paramFormats, int resultFormat) {
    std::cout << "Query:" << std::endl << query << std::endl;
    PGresult *response = PQexecParams(conn, query, nParams, paramTypes, paramValues, paramLengths, paramFormats, resultFormat);

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



std::vector<Post> PQWrapper::getPosts()
{
    std::vector<Post> postList;
    PGresult *users = this->Query("SELECT uName, content, uId, age FROM posts INNER JOIN users ON posts.uName = users.name");
    int rows1 = PQntuples(users);
    postList.reserve(rows1);
    for (int i = 0; i < rows1; ++i) {
        User user(atoi(PQgetvalue(users, i, 0)), PQgetvalue(users, i, 1), atoi(PQgetvalue(users, i, 2)));
        const std::string content(PQgetvalue(users, i, 1));
        Post value(content, &user);
        postList.emplace_back(value);
        // std::cout << "Post"<<i<<": "<< value.toString() << std::endl;
        
    }
    return postList;
}
std::vector<User> PQWrapper::getUsers()
{
    std::vector<User> userList;
    PGresult *users = this->Query("SELECT * FROM users");
    int rows1 = PQntuples(users);
    userList.reserve(rows1);
    for (int i = 0; i < rows1; ++i) {
        User value(atoi(PQgetvalue(users, i, 0)), PQgetvalue(users, i, 1), atoi(PQgetvalue(users, i, 2)));
        std::cout << "User"<<i<<": "<< value.toString() << std::endl;
        userList.emplace_back(value);
        
    }
    return userList;
}


std::vector<Post> PQWrapper::getPostsOf(std::string userName)
{
    std::vector<Post> postList;
    std::string query = "SELECT uName, content, uId, age FROM posts INNER JOIN users ON posts.uName = users.name WHERE posts.uName = $1";
    const char* params[1] = {userName.c_str()};
    PGresult* users = this->QueryParams(query.c_str(), 1, nullptr, params, nullptr, nullptr, 0);
    int rows1 = PQntuples(users);
    postList.reserve(rows1);
    for (int i = 0; i < rows1; ++i) {
        User user(atoi(PQgetvalue(users, i, 0)), PQgetvalue(users, i, 1), atoi(PQgetvalue(users, i, 2)));
        const std::string content(PQgetvalue(users, i, 1));
        Post value(content, &user);
        postList.emplace_back(value);
        // std::cout << "Post"<< i <<": "<< value.toString() << std::endl;
        
    }
    return postList;
}
std::vector<User> PQWrapper::getUsersOf()
{
    // Will be used to get friends/follower list.
}