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

    std::vector<Post> getPosts();
    std::vector<User> getUsers();


    std::vector<Post> getPostsOf(User user);
    std::vector<User> getUsersOf();

};
