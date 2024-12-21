#include "logindialog.h"
#include "ui_logindialog.h"
#include "logindialog.h"
#include <QDebug>
#include <QMessageBox>
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(&loginVM, &LoginViewModel::loginMessageChanged, this, &LoginDialog::updateAlertMsg);
    connect(&loginVM, &LoginViewModel::loginSucess, this, [this]()->void{ this->accept(); });
    connect(&loginVM, &LoginViewModel::loginFail, this, [parent]()->void{
        QMessageBox::critical(parent, "로그인 실패", "로그인에 실패했습니다. 다시 시도해주세요.");
    });

    //connect(&loginVM, &LoginViewModel::editChanged, this, &LoginDialog::on_editID_textChanged);
    //connect(ui->editID, &LoginDialog::on_editID_textChanged, this, &LoginViewModel::editChanged);

//    loginVM.addObserveEvent([]()->void{
//        ///ui->labelMessage->setText(alertMessage);
//    });
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_editID_textChanged(const QString &arg1)
{
    emit loginVM.editIDChanged(arg1);
}


void LoginDialog::on_editPW_textChanged(const QString &arg1)
{
    emit loginVM.editPWChanged(arg1);
}

void LoginDialog::updateAlertMsg(const QString &message)
{
    ui->labelMessage->setText(message);
}

void LoginDialog::on_btnLogin_clicked()
{
    emit loginVM.btnLoginClicked();
}

