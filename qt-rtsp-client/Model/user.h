#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

class User
{
public:
    User();
    bool canLogin(string id, string pw_sha256_key, string server_address="localhost");
};

#endif // USER_H
