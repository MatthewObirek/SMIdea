#pragma once
#include <iostream>

// #include "User.hpp"

class User;

class Post 
{
private:
    std::string contents;


    User* user;
public:
    //Empty Constructor
    Post();
    //Primary Constructor
    Post(const std::string contents, User* user);
    //Copy Constructor
    Post(const Post &obj);
    //Move Constructor
    Post(Post &&obj) noexcept; 
    //Deconstructor
    ~Post();

    //Getters
    inline std::string getContents() { return contents; }
    inline User* getUser() { return user; }
};