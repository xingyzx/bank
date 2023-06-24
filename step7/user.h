#ifndef user_h

#define user_h

#include <string>
#include <iostream>
using namespace std;


class User {
    private:

    string name;


    public:
    User(string name);
    string getName(){return name;}
    void logName(string _name){name=_name;}
    bool operator==(const User& other) const;

};



#endif