#include "user.h"

User::User(string name):name(name){}

bool User::operator==(const User& other) const {
        return (name == other.name) ;
}