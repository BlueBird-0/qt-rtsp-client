#ifndef RTPCLIENT_H
#define RTPCLIENT_H
#include <QString>
#include <QStringList>

class RtpClient
{
public:
    RtpClient();
    static int getWidth() { return 640; }
    static int getHeight() { return 480; }
    static int getChannel() { return 3;}

    static QString getProgram();
    static QStringList getArguments(QString url);
private:
};

#endif // RTPCLIENT_H
