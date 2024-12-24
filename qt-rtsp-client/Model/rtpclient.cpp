#include "rtpclient.h"
#include <iostream>

RtpClient::RtpClient()
{
}

QString RtpClient::getProgram()
{
    QString program;
#if _WIN32 // window
    program = QDir::currentPath() + "/bin/ffmpeg.exe";
#else // linux
    program = "/usr/bin/ffmpeg";
#endif
    return program;
}

QStringList RtpClient::getArguments(QString url)
{
    QStringList arguments;
#if _WIN32 // window
    arguments;
#else // linux
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
#endif
    return arguments;
}
