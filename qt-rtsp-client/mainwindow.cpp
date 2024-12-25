#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streamingwidget.h"
#include "debugwidget.h"
#include "ModelView/rtpclientviewmodel.h"
#include <QDebug>
#include <QPlainTextEdit>

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

    setupPlainTextEditInWidget(ui->Guid);
}

void MainWindow::setupPlainTextEditInWidget(QWidget* parentWidget) {
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit(parentWidget);
    plainTextEdit->setMinimumWidth(240); // 최소 너비 400px 설정
    plainTextEdit->setReadOnly(true);
    plainTextEdit->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: #2b2b2b; /* 어두운 배경 */
            color: #ffffff; /* 흰색 텍스트 */
            font-family: 'Consolas', 'Courier New', monospace; /* 코딩에 적합한 폰트 */
            font-size: 14px; /* 텍스트 크기 */
            border: 2px solid #4c4c4c; /* 테두리 색상 */
            border-radius: 8px; /* 둥근 모서리 */
            padding: 10px; /* 내부 여백 */
        }
        QPlainTextEdit:focus {
            border: 2px solid #6c63ff; /* 포커스 시 테두리 강조 */
        }
    )");

    // 레이아웃 생성 및 설정
    QVBoxLayout* layout = new QVBoxLayout(parentWidget);
    layout->setContentsMargins(5, 5, 5, 5); // 적절한 여백 설정
    layout->setSpacing(0);

    // QPlainTextEdit 추가
    layout->addWidget(plainTextEdit);
    parentWidget->setLayout(layout);

    // 초기 텍스트 (선택사항)
    plainTextEdit->setPlainText("This is Qt example Client!\n"
                                "Qt로 개발한 예시용 클라이언트 입니다.\n"
                                "MVVM 구조로 개발되었습니다.\n\n\n"
                                "-- 설명 --\n"
                                "Video 실시간 스트리밍을 수행합니다.\n"
                                "내부적으로 RTSP 를 사용합니다. 따라서 영상 테스트를 위해서 RTSP 서버가 필요합니다.\n\n\n"
                                "-- Git repository --\n"
                                "https://github.com/BlueBird-0/qt-rtsp-client\n"
                                "*MIT License를 따릅니다.\n\n\n"

                                "-- 시작하기 --\n"
                                "Mouse RightClick > New Tab");
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
    } );

    //debug Text 동적 연결
    mainVM->streamingVMVector.back()->rtpClientVM->setDebugText(newDebugTabWidget->getDebugTextPtr());
//    connect(mainVM->streamingVMVector.back()->rtpClientVM, &RtpClientViewModel::signal_ffmpeg_debug, this, []()->void{
//    } );
    connect(mainVM->streamingVMVector.back()->rtpClientVM, &RtpClientViewModel::signal_ffmpeg_debug, newVM, &DebugViewModel::writeDebug);
}

MainWindow::~MainWindow()
{
    delete ui;
}

