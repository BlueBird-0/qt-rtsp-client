#include "streamingviewmodel.h"
#include "rtpclientviewmodel.h"
#include <QDebug>

StreamingViewModel::StreamingViewModel(QObject *parent)
    : ViewModel{parent}
{
    rtpClientVM = new RtpClientViewModel();
}

StreamingViewModel::~StreamingViewModel()
{
    delete rtpClientVM;
}

void StreamingViewModel::startStreaming(const QString &url)
{
    rtpClientVM->startFFmpegProcess(url);
}

