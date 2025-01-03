#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "ModelView/mainviewmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupPlainTextEditInWidget(QWidget* parentWidget);
    ~MainWindow();

private slots:
    void showRightClickMenu(const QPoint& pos);
    void addStreamingWidget(StreamingViewModel* newVM);
    void addDebugWidget(DebugViewModel* newVM);

private:
    Ui::MainWindow *ui;
    QMenu rightClickMenu;
    MainViewModel *mainVM;
};
#endif // MAINWINDOW_H
