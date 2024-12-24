#include "loginviewmodel.h"
#include "Model/login.h"
#include <QDebug>
#include <QCryptographicHash>

LoginViewModel::LoginViewModel(QObject* parent) : ViewModel(parent)
{
}

string LoginViewModel::validateLogin(const string id, const string pw)
{
    // 조건1: id는 최소 4글자 이상이어야 한다.
    if (id.length() < 4) {
        return "ID는 최소 4글자 이상이어야 합니다.";
    }

    // 조건2: id가 공백이어서는 안 된다.
    if (id.find_first_not_of(' ') == std::string::npos) {
        return "ID가 공백입니다.";
    }

    // 조건3: pw가 공백이어서는 안 된다.
    if (pw.find_first_not_of(' ') == std::string::npos) {
        return "PW가 공백입니다.";
    }

    // 모든 조건을 통과한 경우
    return "";
}

string LoginViewModel::hashSHA256(const QString& plainText)
{
    QByteArray hash = QCryptographicHash::hash(plainText.toUtf8(), QCryptographicHash::Sha256);
    return hash.toStdString();
}

void LoginViewModel::editIDChanged(const QString &arg1)
{
    m_id = arg1.toStdString();
    QString msg = QString(validateLogin(m_id, m_pw).c_str());
    emit loginMessageChanged(msg);
}

void LoginViewModel::editPWChanged(const QString &arg1)
{
    m_pw = arg1.toStdString();
    QString msg = QString(validateLogin(m_id, m_pw).c_str());
    emit loginMessageChanged(msg);
}

void LoginViewModel::btnLoginClicked()
{
    bool success = Login::login(m_id, hashSHA256(QString(m_pw.c_str())), std::string("localhost"));
    if(success)
        emit loginSucess();
    else
        emit loginFail();
}
