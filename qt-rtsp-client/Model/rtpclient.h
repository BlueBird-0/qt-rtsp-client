#ifndef RTPCLIENT_H
#define RTPCLIENT_H

#include <QObject>
class QProcess;
class QLabel;

class RtpClient : public QObject
{
    Q_OBJECT
public:
    static RtpClient* instance();
    RtpClient();
    RtpClient(const RtpClient &) = delete;
    ~RtpClient() override;
    RtpClient &operator=(const RtpClient &) = delete;
    // FFmpeg 프로세스 시작 및 데이터 읽기 메서드
    void startFFmpegProcess(QString url);
    void finishFfmpeg();
    // FFmpeg 프로세스 관리용 변수
    QProcess *ffmpegProcess = nullptr;
    QLabel *videoLabel = nullptr;

private:
    QByteArray* buffer;
public slots:
    void readFFmpegOutput();

    // void recv_url(QString url);
signals:
    void signal_ffmpeg_debug(QString, RtpClient*);
    void signal_streaming_start();
    void signal_video_start();
    void signal_stream_fail();
};

#endif // RTPCLIENT_H
