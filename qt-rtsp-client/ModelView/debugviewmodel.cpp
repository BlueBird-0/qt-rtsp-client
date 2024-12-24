#include "debugviewmodel.h"
#include "rtpclientviewmodel.h"
#include <QPlainTextEdit>
#include <QDebug>

DebugViewModel::DebugViewModel()
{

}

void DebugViewModel::writeDebug(QString error, RtpClientViewModel *textedit_key)
{
    qDebug() << "call writeDebug()";
    if(textedit_key->getDebugText() != nullptr)
    {
        textedit_key->getDebugText()->appendPlainText(error);
    }
}
