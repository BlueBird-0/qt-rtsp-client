#include "viewmodel.h"

ViewModel::ViewModel(QObject* parent) : QObject(parent) {}

void ViewModel::displayUpdate()
{
    for(auto e: event_vector)
        e();
}

void ViewModel::addObserveEvent(std::function<void()> event)
{
    event_vector.push_back(event);
}
