#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include "viewmodel.h"
#include <iostream>
#include <functional>
using namespace std;

class LoginViewModel : public ViewModel
{
    Q_OBJECT
private:
    std::string m_id, m_pw;
    string validateLogin(const string id, const string pw);
    string hashSHA256(const QString& plainText);

public:
    explicit LoginViewModel(QObject* parent = nullptr);

signals:
    void loginMessageChanged(const QString &message);
    void loginSucess();
    void loginFail();

public slots:
    void editIDChanged(const QString &arg1);
    void editPWChanged(const QString &arg1);
    void btnLoginClicked();
};

#endif // LOGINVIEWMODEL_H
