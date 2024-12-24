#ifndef RTPCLIENTVIEWMODEL_H
#define RTPCLIENTVIEWMODEL_H
#include "viewmodel.h"
#include "Model/rtpclient.h"
class QProcess;
class QLabel;

class RtpClientViewModel : public ViewModel
{
    Q_OBJECT
public:
    RtpClientViewModel();
    RtpClientViewModel(const RtpClientViewModel &) = delete;
    ~RtpClientViewModel() override;
    RtpClientViewModel &operator=(const RtpClientViewModel &) = delete;
    // FFmpeg 프로세스 시작 및 데이터 읽기 메서드
    void startFFmpegProcess(QString url);
    void finishFfmpeg();
    void setVideoLabel(QLabel* labelPtr) { this->videoLabel = labelPtr; };

private:
//    RtpClient rtpClient;
    QByteArray* buffer;
    QLabel *videoLabel = nullptr;
    QProcess *ffmpegProcess = nullptr;    // FFmpeg 프로세스 관리용 변수

signals:
    void signal_ffmpeg_debug(QString, RtpClientViewModel*);
    void signal_streaming_start();
    void signal_streaming_finish();
    void signal_video_start();
    void signal_streaming_fail();
public slots:
    void callStreamingFinish();
    void readFFmpegOutput();
};

#endif // RTPCLIENTVIEWMODEL_H
