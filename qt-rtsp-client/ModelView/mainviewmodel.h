#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "viewmodel.h"
#include "streamingviewmodel.h"
#include <vector>

class MainViewModel : public ViewModel
{
    Q_OBJECT
public:
    explicit MainViewModel(QObject *parent = nullptr);

signals:
    void finishNewStreamingVM(StreamingViewModel* newVM);

public slots:
    void addNewStreamingVM();

private:
    std::vector<StreamingViewModel*> streamingVMVector;
};

#endif // MAINVIEWMODEL_H
