#ifndef ISERVER_H
#define ISERVER_H

#include <QWidget>

#include "IObserver.h"

class IServer : public QWidget
{
public:
    virtual void attach(IObserver *observer) noexcept = 0;
    virtual void detach(IObserver *observer) noexcept = 0;
    virtual void notify(bool canConnect) noexcept = 0;
    virtual bool startRunning() = 0;
    virtual bool stopRunning() = 0;
};

#endif // ISERVER_H
