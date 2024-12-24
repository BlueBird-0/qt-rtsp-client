#ifndef STREAMINGVIEWMODEL_H
#define STREAMINGVIEWMODEL_H

#include "viewmodel.h"
class RtpClientViewModel;

class StreamingViewModel : public ViewModel
{
    Q_OBJECT
private:

public:
    RtpClientViewModel* rtpClientVM;
    explicit StreamingViewModel(QObject *parent = nullptr);
    ~StreamingViewModel();

public slots:
    void startStreaming(const QString &url);
};

#endif // STREAMINGVIEWMODEL_H
