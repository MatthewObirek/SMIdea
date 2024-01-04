#include "User.hpp"


//Empty constructor
User::User() : User(-1, "NoName", 0) {}
//Primary constructor
User::User(int id, const std::string name, int age) :id(id), name(name), age(age) {}
//Copy Constructor
User::User(const User &obj) : id(obj.id), name(obj.name), age(obj.age) {}
//Move Constructor
User::User(User &&obj) noexcept 
    : id(std::move(obj.id)), name(std::move(obj.name)), age(std::move(obj.age)) {} 
//Deconstructor
User::~User() {}