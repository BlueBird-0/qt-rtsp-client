#include "logindialog.h"
#include "ui_logindialog.h"
#include "logindialog.h"
#include <QDebug>
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(&loginVM, &LoginViewModel::loginMessageChanged, this, &LoginDialog::updateAlertMsg);

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
