#ifndef LOGINMODEL_H
#define LOGINMODEL_H
#include <iostream>
using namespace std;

class LoginModel
{
public:
    LoginModel();
    static string serverSHA256(const string& plain);
    static bool login(string id, string pw_sha256_key, string server_address="localhost");
};

#endif // LOGINMODEL_H
