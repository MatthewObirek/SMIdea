#include "Post.hpp"
#include "User.hpp"

Post::Post() : Post("NULL", nullptr) {}

Post::Post(const std::string contents, User* user) : contents(contents), user(user) {}
//Copy Constructor
Post::Post(const Post &obj) : contents(obj.contents), user(obj.user) {}
//Move Constructor
Post::Post(Post &&obj) noexcept 
    : contents(std::move(obj.contents)), user(std::move(obj.user)) {} 
//Deconstructor
Post::~Post() { delete user; }