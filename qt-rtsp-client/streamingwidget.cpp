#include "streamingwidget.h"
#include "ui_streamingwidget.h"
#include <QAction>
#include "ModelView/rtpclientviewmodel.h"

StreamingWidget::StreamingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StreamingWidget)
{
    ui->setupUi(this);

    // QLineEdit에 아이콘 추가
    QLineEdit *lineEditURL = ui->editURL;
    lineEditURL->setPlaceholderText("rtsp://localhost:8554"); // 힌트 텍스트 추가
    QAction *iconActionURL = new QAction(lineEditURL);
    iconActionURL->setIcon(QIcon(":/images/Resources/link_icon.png")); // 아이콘 경로 설정
    lineEditURL->addAction(iconActionURL, QLineEdit::LeadingPosition);

    static int streamingWidgetId = 0;
    setWindowTitle(QString("New Tab") + QString::number(streamingWidgetId+1));
    this->streamingWidgetId = streamingWidgetId++;
    lineEditURL->setFocus();
}

StreamingWidget::StreamingWidget(StreamingViewModel *streamingVM, QWidget *parent)
    : StreamingWidget(parent)
{
    streamingVM->rtpClientVM->setVideoLabel(ui->video_label);
    this->streamingVM = streamingVM;

    connect(streamingVM->rtpClientVM, &RtpClientViewModel::signal_streaming_start, this, [this]()->void{ ui->widget->hide(); });
    connect(streamingVM->rtpClientVM, &RtpClientViewModel::signal_streaming_fail, this, [this]()->void{ ui->widget->show(); });
    connect(streamingVM->rtpClientVM, &RtpClientViewModel::signal_streaming_finish, this, [this]()->void{ ui->widget->show();} );

}


StreamingWidget::~StreamingWidget()
{
    delete streamingVM;
    delete ui;
}

void StreamingWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event); // 기본 resize 이벤트 처리
    ui->video_label->resize(this->size());  // QLabel 크기를 창 크기로 조정

    // 이미지를 QLabel 크기에 맞게 조정
    QPixmap originalPixmap(":/images/Resources/streamingWidgetBackground.png"); // 리소스에서 이미지 불러오기
    if (!originalPixmap.isNull()) {
        ui->video_label->setPixmap(
            originalPixmap.scaled(
                ui->video_label->size(),    // QLabel 크기에 맞게 스케일링
                Qt::KeepAspectRatio,       // 비율 유지 (이미지가 찌그러지지 않도록)
                Qt::SmoothTransformation   // 부드러운 스케일링
                )
            );
    }
}

void StreamingWidget::on_btnUrlEnter_clicked()
{
    emit streamingVM->startStreaming(ui->editURL->text());
}

