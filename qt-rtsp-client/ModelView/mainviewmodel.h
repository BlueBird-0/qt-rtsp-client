#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "viewmodel.h"
#include <vector>
class StreamingViewModel;
class DebugViewModel;

class MainViewModel : public ViewModel
{
    Q_OBJECT
public:
    std::vector<StreamingViewModel*> streamingVMVector;
    std::vector<DebugViewModel*> debugVMVector;
    explicit MainViewModel(QObject *parent = nullptr);

signals:
    void finishNewStreamingVM(StreamingViewModel* newVM);
    void finishNewDebugVM(DebugViewModel* newVM);

public slots:
    void addNewTabVM();

private:
};

#endif // MAINVIEWMODEL_H
