#ifndef DEBUGVIEWMODEL_H
#define DEBUGVIEWMODEL_H

#include "viewmodel.h"
#include "rtpclientviewmodel.h"
class DebugViewModel : public ViewModel
{
    Q_OBJECT
public:
    DebugViewModel();
public slots:
    void writeDebug(QString error, RtpClientViewModel* textedit_key);
};

#endif // DEBUGVIEWMODEL_H
