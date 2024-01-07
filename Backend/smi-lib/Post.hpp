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
    Post();
    
    Post(const std::string contents, User* user);
};