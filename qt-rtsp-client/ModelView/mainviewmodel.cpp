#include "mainviewmodel.h"
#include "streamingviewmodel.h"
#include "debugviewmodel.h"
#include "ModelView/rtpclientviewmodel.h"
#include <QDebug>

MainViewModel::MainViewModel(QObject *parent)
    : ViewModel{parent}
{

}

void MainViewModel::addNewTabVM()
{
    StreamingViewModel* newStreamVM = new StreamingViewModel();
    streamingVMVector.push_back(newStreamVM);

    DebugViewModel* newDebugVM = new DebugViewModel();
    debugVMVector.push_back(newDebugVM);

    emit finishNewStreamingVM(newStreamVM);
    emit finishNewDebugVM(newDebugVM);
}
