#include "streamingviewmodel.h"
#include "Model/rtpclient.h"
#include <QDebug>

StreamingViewModel::StreamingViewModel(QObject *parent)
    : ViewModel{parent}
{
    rtpClient = new RtpClient();
}

void StreamingViewModel::startStreaming(const QString &url)
{
    qDebug() << "startStreaming";
    rtpClient->startFFmpegProcess(url);
}

