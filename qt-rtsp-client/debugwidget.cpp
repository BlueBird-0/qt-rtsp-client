#include "debugwidget.h"
#include "ui_debugwidget.h"

DebugWidget::DebugWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugWidget)
{
    ui->setupUi(this);

    static int debugWidgetId=0;
    setWindowTitle(QString("New Tab") + QString::number(debugWidgetId+1));
    this->debugWidgetId = debugWidgetId++;
}

DebugWidget::DebugWidget(DebugViewModel *debugVM, QWidget *parent)
    : DebugWidget(parent)
{
    this->debugVM = debugVM;
}

DebugWidget::~DebugWidget()
{
    delete debugVM;
    delete ui;
}

QLineEdit *DebugWidget::getDurationPtr()
{
    return ui->lineEditDuration;
}
