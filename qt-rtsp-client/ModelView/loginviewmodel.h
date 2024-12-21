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

public:
    explicit LoginViewModel(QObject* parent = nullptr);

signals:
    void loginMessageChanged(const QString &message);
public slots:
    void editIDChanged(const QString &arg1);
    void editPWChanged(const QString &arg1);

};

#endif // LOGINVIEWMODEL_H
