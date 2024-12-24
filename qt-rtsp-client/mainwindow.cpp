#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streamingwidget.h"
#include "debugwidget.h"
#include "ModelView/rtpclientviewmodel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/Resources/application_icon.png"));
    ui->mainTabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mainVM = new MainViewModel();
    connect(ui->mainTabWidget, &QTabWidget::customContextMenuRequested, this, &MainWindow::showRightClickMenu);

    connect(ui->actionNew_Tab, &QAction::triggered, mainVM, &MainViewModel::addNewTabVM);
    rightClickMenu.addAction(ui->actionNew_Tab);

    connect(mainVM, &MainViewModel::finishNewStreamingVM, this, &MainWindow::addStreamingWidget);
    connect(mainVM, &MainViewModel::finishNewDebugVM, this, &MainWindow::addDebugWidget);
}

void MainWindow:: showRightClickMenu(const QPoint& pos)
{
    rightClickMenu.exec(ui->mainTabWidget->mapToGlobal(pos));
}

void MainWindow::addStreamingWidget(StreamingViewModel* newVM)
{
    StreamingWidget * newWidget = new StreamingWidget(newVM, this);
    ui->mdiArea->addSubWindow(newWidget);
    newWidget->show();
    ui->mdiArea->tileSubWindows();
}

void MainWindow::addDebugWidget(DebugViewModel* newVM)
{
    DebugWidget* newDebugTabWidget = new DebugWidget(newVM, this);
    ui->tabWidget->addTab(newDebugTabWidget, newDebugTabWidget->windowTitle());

    mainVM->streamingVMVector.back()->rtpClientVM->setDurationLabel(newDebugTabWidget->getDurationPtr());
    // streaming 탭과 동적연결 (삭제처리)
    connect(mainVM->streamingVMVector.back(), &QObject::destroyed, this, [this, newDebugTabWidget]() {
        int tabIndex = ui->tabWidget->indexOf(newDebugTabWidget);
        if (tabIndex != -1) {
            ui->tabWidget->removeTab(tabIndex);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

