#include "mainviewmodel.h"
#include "streamingviewmodel.h"
#include <QDebug>

MainViewModel::MainViewModel(QObject *parent)
    : ViewModel{parent}
{

}

void MainViewModel::addNewStreamingVM()
{
    StreamingViewModel* newVM = new StreamingViewModel();
    streamingVMVector.push_back(newVM);
    emit finishNewStreamingVM(newVM);
}
