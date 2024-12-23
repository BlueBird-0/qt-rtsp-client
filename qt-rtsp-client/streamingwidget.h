#ifndef STREAMINGWIDGET_H
#define STREAMINGWIDGET_H

#include <QWidget>
#include "ModelView/streamingviewmodel.h"

namespace Ui {
class StreamingWidget;
}

class StreamingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StreamingWidget(QWidget *parent = nullptr);
    StreamingWidget(StreamingViewModel *streamingVM, QWidget *parent = nullptr);
    ~StreamingWidget();

private:
    Ui::StreamingWidget *ui;
    StreamingViewModel *streamingVM;
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_btnUrlEnter_clicked();
};

#endif // STREAMINGWIDGET_H
