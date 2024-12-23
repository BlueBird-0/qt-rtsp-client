#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include "ModelView/loginviewmodel.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_editID_textChanged(const QString &arg1);
    void on_editPW_textChanged(const QString &arg1);

    void updateAlertMsg(const QString &message);

    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    LoginViewModel* loginVM;
    //QString id, pw;
};

#endif // LOGINDIALOG_H
