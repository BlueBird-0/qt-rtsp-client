#ifndef LOGIN_H
#define LOGIN_H
#include <iostream>
using namespace std;

class Login
{
public:
    Login();
    static string serverSHA256(const string& plain);
    static bool login(string id, string pw_sha256_key, string server_address="localhost");
};

#endif // LOGIN_H
