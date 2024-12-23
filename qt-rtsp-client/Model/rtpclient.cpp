#include "Model/rtpclient.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QDir>
#include <QPainter>

RtpClient* RtpClient::instance() {
    static RtpClient instance;
    return &instance;
}

RtpClient::RtpClient() {
    buffer = new QByteArray;
}

RtpClient::~RtpClient()
{

    qDebug() <<"!!!!~rtpCLient()!!!!!";
    if (ffmpegProcess) {
        if (ffmpegProcess->state() != QProcess::NotRunning) {
            qDebug() << "Waiting for FFmpeg to finish...";
            finishFfmpeg(); // ?븞?쟾?븳 醫낅즺 ?샇異?
        }
        delete ffmpegProcess;
    }
    qDebug()<<"!!!rtpCLient finished!!!!";
}

void RtpClient::readFFmpegOutput() {
    static QSize cachedLabelSize; // 라벨 크기 캐시
    static QPixmap cachedFinalPixmap; // 검은 배경용 QPixmap
    static bool sizeChanged = true; // 라벨 크기 변경 여부

    if (videoLabel->size() != cachedLabelSize) {
        // 라벨 크기가 변경되었을 때만 검은 배경 갱신
        cachedLabelSize = videoLabel->size();
        sizeChanged = true;

        // 검은색 배경의 QPixmap 생성
        cachedFinalPixmap = QPixmap(cachedLabelSize);
        cachedFinalPixmap.fill(Qt::black);
    }

    // FFmpeg 데이터 읽기
    QByteArray data = ffmpegProcess->readAllStandardOutput();
    if (data.isEmpty()) {
        return;
    }

    buffer->append(data);
    //qDebug() << "Buffer size:" << buffer->size();
    //qDebug() << "Frame size required:" << 640 * 480 * 3;

    if (buffer->size() >= 640 * 480 * 3) {
        QByteArray frameData = buffer->left(640 * 480 * 3);
        buffer->remove(0, 640 * 480 * 3);

        QImage image(reinterpret_cast<const uchar*>(frameData.data()), 640, 480, QImage::Format_RGB888);

        if (!image.isNull()) {
            // 이미지 크기를 라벨 크기에 맞게 조정
            QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(cachedLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            QPixmap finalPixmap = cachedFinalPixmap; // 검은 배경 복사
            QPainter painter(&finalPixmap);

            // 검은 배경 위에 조정된 이미지를 중앙에 그리기
            painter.drawPixmap((cachedLabelSize.width() - scaledPixmap.width()) / 2,
                               (cachedLabelSize.height() - scaledPixmap.height()) / 2,
                               scaledPixmap);

            // 라벨에 최신 이미지를 설정
            videoLabel->setPixmap(finalPixmap);
            sizeChanged = false; // 크기 변경 상태 초기화
        } else {
            qDebug() << "Failed to create QImage";
        }

        emit signal_video_start();
    }
}

void RtpClient::startFFmpegProcess(QString url) {
    ffmpegProcess = new QProcess();
#if _WIN32 // window
    QString program = QDir::currentPath() + "/bin/ffmpeg.exe";
    qDebug() << program;
    QStringList arguments;
#else // linux
    QString program = "/usr/bin/ffmpeg";
    qDebug() << program;
    QStringList arguments;
#endif
    arguments << "-protocol_whitelist" << "file,tcp,udp,rtp,rtsp"
              //<< "-hwaccel" << "cuda"                            // 하드웨어 가속 (CUDA)
              << "-i" << url // "rtsp://192.168.1.15:8554"
              << "-s" << "640x480"
              << "-vsync" << "vfr" // 비디오 동기화
              << "-framerate" << "30" // 30fps로 제한
              << "-pix_fmt" << "rgb24"
              //<<"-threads"<<"1"
              << "-b:v" << "2M"
              << "-maxrate" << "2M"
              << "-bufsize" << "4M"
              << "-f" << "rawvideo"
              //<< "-loglevel" << "debug"
              << "-";                  // stdout

    //  FFmpeg
    ffmpegProcess->start(program, arguments);

    connect(ffmpegProcess, &QProcess::readyReadStandardError, this, [this]() {
        QByteArray errorOutput = ffmpegProcess->readAllStandardError();
        qDebug() << "----------------------------------";
        if (!errorOutput.isEmpty()) {
            if(errorOutput.contains("failed")||errorOutput.contains("No such file")||errorOutput.contains("not found")||errorOutput.contains("Invalid argument")||errorOutput.contains("Bad Request"))
            {
                emit signal_stream_fail();
                emit signal_ffmpeg_debug("FFmpeg error output:"+errorOutput,this);
            }
            emit signal_ffmpeg_debug("FFmpeg error output:"+errorOutput,this);
            qDebug()<<"ffmepg debug : "<<errorOutput;
        }
    });

    if (!ffmpegProcess->waitForStarted()) {
        qDebug() << "FFmpeg : " << ffmpegProcess->errorString();
    } else {
        qDebug() << "FFmpeg ...";
        emit signal_streaming_start();
        QObject::connect(ffmpegProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readFFmpegOutput()));
    }

}
void RtpClient::finishFfmpeg()
{
    if(ffmpegProcess)
    {qDebug()<<"finishFFmpge";
        ffmpegProcess->terminate();
        if(!ffmpegProcess->waitForFinished(5000))
        {
            ffmpegProcess->kill();
        }
    }
}
