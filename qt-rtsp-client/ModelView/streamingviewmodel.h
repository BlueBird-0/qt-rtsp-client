#ifndef STREAMINGVIEWMODEL_H
#define STREAMINGVIEWMODEL_H

#include "viewmodel.h"
class RtpClient;

class StreamingViewModel : public ViewModel
{
    Q_OBJECT
private:
    RtpClient* rtpClient;

public:
    explicit StreamingViewModel(QObject *parent = nullptr);

public slots:
    void startStreaming(const QString &url);
};

#endif // STREAMINGVIEWMODEL_H
