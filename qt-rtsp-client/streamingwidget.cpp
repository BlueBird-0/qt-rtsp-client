#include "streamingwidget.h"
#include "ui_streamingwidget.h"

StreamingWidget::StreamingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StreamingWidget)
{
    ui->setupUi(this);
}

StreamingWidget::StreamingWidget(const StreamingViewModel *streamingVM, QWidget *parent)
    : StreamingWidget(parent)
{
    this->streamingVM = streamingVM;
}


StreamingWidget::~StreamingWidget()
{
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
