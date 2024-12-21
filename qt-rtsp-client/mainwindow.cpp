#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "loginDialog";
    LoginDialog loginDlg;
    int ret = loginDlg.exec();
    if(ret == QDialog::Accepted){
        qDebug() << "QDialog Accepted";
    } else if(ret == QDialog::Rejected){
        qDebug() << "QDialog Rejected";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

