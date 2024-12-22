#include "loginmodel.h"
#include <cstring>
#include <QDebug>
#include <QCryptographicHash>

LoginModel::LoginModel() {}


string LoginModel::serverSHA256(const string& plain)
{
    QByteArray hash = QCryptographicHash::hash(plain, QCryptographicHash::Sha256);
    return hash.toStdString();
}

bool LoginModel::login(string id, string pw_sha256_key, string server_address)
{
    qDebug() << pw_sha256_key;
    qDebug() << serverSHA256("1234");

    if(id == string("qwerty") && pw_sha256_key == serverSHA256("1234")){
        qDebug() << "로그인 성공";
        return true;
    }

    qDebug() << "로그인 실패";
    return false;
}
