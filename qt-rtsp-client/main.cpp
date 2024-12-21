#include "mainwindow.h"

#include <QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDlg;
    int ret = loginDlg.exec();
    if(ret == QDialog::Accepted){
        qDebug() << "login Dialog Accepted";
    }else if(ret == QDialog::Rejected){
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
