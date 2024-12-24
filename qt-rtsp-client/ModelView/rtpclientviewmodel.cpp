#include "ModelView/rtpclientviewmodel.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QDir>
#include <QPainter>
#include <QLineEdit>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>

RtpClientViewModel::RtpClientViewModel() {
    buffer = new QByteArray;
}

RtpClientViewModel::~RtpClientViewModel()
{
    qDebug() <<"!!!!~RtpClientViewModel()!!!!!";
    if (ffmpegProcess) {
        if (ffmpegProcess->state() != QProcess::NotRunning) {
            qDebug() << "Waiting for FFmpeg to finish...";
            finishFfmpeg(); // ?븞?쟾?븳 醫낅즺 ?샇異?
        }        
        finishFfmpeg();
        delete ffmpegProcess;
    }
    qDebug()<<"!!!RtpClientViewModel finished!!!!";
}

void RtpClientViewModel::callStreamingFinish()
{
    updateTimer->stop(); // 1초마다 경과 시간 업데이트
    emit signal_streaming_finish();
}

void RtpClientViewModel::readFFmpegOutput() {
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
    int width = RtpClient::getWidth();
    int height = RtpClient::getHeight();
    int channel = RtpClient::getChannel();
    //qDebug() << "Buffer size:" << buffer->size();
    //qDebug() << "Frame size required:" << width * height * channel;

    if (buffer->size() >= width * height * channel) {
        QByteArray frameData = buffer->left(640 * height * channel);
        buffer->remove(0, width * height * channel);

        QImage image(reinterpret_cast<const uchar*>(frameData.data()), width, height, QImage::Format_RGB888);

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

void RtpClientViewModel::updateElapsedTime()
{
    // 경과 시간 계산 및 표시
    qint64 elapsedMs = elapsedTimer->elapsed();
    QTime time = QTime(0, 0).addMSecs(elapsedMs);

    duration->setText(time.toString("hh:mm:ss"));
}

void RtpClientViewModel::startFFmpegProcess(QString url) {
    ffmpegProcess = new QProcess();
    //  FFmpeg
    ffmpegProcess->start(RtpClient::getProgram(), RtpClient::getArguments(url));

    // set Timer
    elapsedTimer = new QElapsedTimer();
    updateTimer = new QTimer(this);

    connect(updateTimer, &QTimer::timeout, this, &RtpClientViewModel::updateElapsedTime);

    connect(ffmpegProcess, &QProcess::readyReadStandardError, this, [this]() {
        QByteArray errorOutput = ffmpegProcess->readAllStandardError();
//        qDebug() << "----------------------------------";
        if (!errorOutput.isEmpty()) {
            if(errorOutput.contains("failed")||errorOutput.contains("No such file")||errorOutput.contains("not found")||errorOutput.contains("Invalid argument")||errorOutput.contains("Bad Request"))
            {
                emit signal_streaming_fail();
                emit signal_ffmpeg_debug("FFmpeg error output:"+errorOutput,this);
            }
            emit signal_ffmpeg_debug("FFmpeg error output:"+errorOutput,this);
//            qDebug()<<"ffmepg debug : "<<errorOutput;
        }
    });

    if (!ffmpegProcess->waitForStarted()) {
        qDebug() << "FFmpeg : " << ffmpegProcess->errorString();
    } else {
        qDebug() << "FFmpeg ...";
        emit signal_streaming_start();
        elapsedTimer->start(); // 경과 시간 타이머 시작
        updateTimer->start(1000); // 1초마다 경과 시간 업데이트
        connect(ffmpegProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readFFmpegOutput()));
        connect(ffmpegProcess, SIGNAL(finished(int)), this, SLOT(callStreamingFinish()));
    }

}
void RtpClientViewModel::finishFfmpeg()
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
