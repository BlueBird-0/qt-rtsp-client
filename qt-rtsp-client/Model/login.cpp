#include "login.h"
#include <cstring>
#include <QDebug>
#include <QCryptographicHash>
#include <QByteArray>

Login::Login() {}

string Login::serverSHA256(const string& plain)
{
    QByteArray plainArray = QString::fromStdString(plain).toUtf8();
    QByteArray hash = QCryptographicHash::hash(plainArray, QCryptographicHash::Sha256);
    return hash.toStdString();
}

bool Login::login(string id, string pw_sha256_key, string server_address)
{
    qDebug() << QString::fromStdString(pw_sha256_key);
    qDebug() << QString::fromStdString(serverSHA256("1234"));

    if(id == string("qwerty") && pw_sha256_key == serverSHA256("1234")){
        qDebug() << QString::fromStdString("로그인 성공");
        return true;
    }

    qDebug() << QString::fromStdString("로그인 실패");
    return false;
}
