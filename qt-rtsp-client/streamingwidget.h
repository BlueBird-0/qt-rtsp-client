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
    StreamingWidget(const StreamingViewModel *streamingVM, QWidget *parent = nullptr);
    ~StreamingWidget();

private:
    Ui::StreamingWidget *ui;
    const StreamingViewModel *streamingVM;
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // STREAMINGWIDGET_H
