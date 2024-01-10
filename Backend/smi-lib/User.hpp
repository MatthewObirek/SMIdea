#pragma once
#include <iostream>
#include <vector>

class Post;

class User
{
private:
    int id;
    int age;
    std::string name;

    std::vector<Post> postList;    
public:
    //Empty constructor
    User();
    //Primary constructor
    User(int id, const std::string name, int age);
    //Copy Constructor
    User(const User &obj);
    //Move Constructor
    User(User &&obj) noexcept; 
    //Deconstructor
    ~User();

    //Getters
    inline int getAge() { return age; }
    inline int getId() { return id; }
    inline std::string getName() { return name; }
    inline std::vector<Post> getPostList() { return postList; }

    std::string toString();
};