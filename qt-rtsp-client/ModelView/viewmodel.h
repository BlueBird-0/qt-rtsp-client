#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <vector>
#include <iostream>
#include <functional>
#include <QObject>

class ViewModel : public QObject
{
    Q_OBJECT

public:
    explicit ViewModel(QObject* parent = nullptr);

    virtual void displayUpdate();
    void addObserveEvent(std::function<void()> event);

signals:
private:
    std::vector<std::function<void()>> event_vector;
};

#endif // VIEWMODEL_H
