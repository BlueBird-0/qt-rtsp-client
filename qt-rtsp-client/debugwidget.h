#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QWidget>
#include "ModelView/debugviewmodel.h"

namespace Ui {
class DebugWidget;
}
class QLineEdit;
class QPlainTextEdit;

class DebugWidget : public QWidget
{
    Q_OBJECT

public:
    int debugWidgetId = 0;
    DebugWidget(DebugViewModel *debugVM, QWidget *parent = nullptr);
    ~DebugWidget();
    QLineEdit* getDurationPtr();
    QPlainTextEdit* getDebugTextPtr();
private:
    Ui::DebugWidget *ui;
    explicit DebugWidget(QWidget *parent = nullptr);
    DebugViewModel *debugVM;
};

#endif // DEBUGWIDGET_H
