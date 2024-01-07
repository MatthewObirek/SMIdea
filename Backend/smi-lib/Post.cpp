#include "Post.hpp"
#include "User.hpp"

Post::Post() : Post("NULL", nullptr) {}

Post::Post(const std::string contents, User* user) : contents(contents), user(user) {}