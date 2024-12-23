#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabBar>
#include "streamingwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/Resources/application_icon.png"));
    ui->mainTabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->mainTabWidget, &QTabWidget::customContextMenuRequested, this, &MainWindow::showRightClickMenu);

    connect(ui->actionNew_Tab, &QAction::triggered, &mainVM, &MainViewModel::addNewStreamingVM);
    rightClickMenu.addAction(ui->actionNew_Tab);

    connect(&mainVM, &MainViewModel::finishNewStreamingVM, this, &MainWindow::addStreamingWidget);
}

void MainWindow:: showRightClickMenu(const QPoint& pos)
{
    rightClickMenu.exec(ui->mainTabWidget->mapToGlobal(pos));
}

void MainWindow::addStreamingWidget(const StreamingViewModel* newVM)
{
    StreamingWidget * newWidget = new StreamingWidget(newVM, this);
    ui->mdiArea->addSubWindow(newWidget);
    newWidget->show();
    ui->mdiArea->tileSubWindows();
}

MainWindow::~MainWindow()
{
    delete ui;
}

