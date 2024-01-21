#pragma once
#include <libpq-fe.h>
#include <vector>

#include <Post.hpp>
#include <User.hpp>

class PQWrapper {
private:
    PGconn *conn;
public:
    PQWrapper(const char *connInfo);

    PGresult* Query(const char *query);
    PGresult* QueryParams(const char *query, int nParams, const Oid* paramTypes,
                                 const char* const* paramValues, const int* paramLengths,
                                 const int* paramFormats, int resultFormat);

    std::vector<Post> getPosts();
    std::vector<User> getUsers();


    std::vector<Post> getPostsOf(std::string userName);
    std::vector<User> getUsersOf();

};
