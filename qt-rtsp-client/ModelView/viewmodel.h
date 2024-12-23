#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <QObject>

class ViewModel : public QObject
{
    Q_OBJECT

public:
    explicit ViewModel(QObject* parent = nullptr);

signals:
private:
};

#endif // VIEWMODEL_H
