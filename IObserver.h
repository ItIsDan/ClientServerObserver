#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QWidget>

class IObserver : public QWidget
{
public:
    virtual void updateEvent(bool canConnect) = 0;
};

#endif // IOBSERVER_H
