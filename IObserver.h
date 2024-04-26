#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QWidget>

class IServer;

class IObserver : public QWidget
{
    Q_OBJECT
public:
    virtual void updateEvent(bool canRun) = 0;
    virtual void setServer(IServer *server) = 0;
signals:
    void connectRequest(bool);
};

#endif // IOBSERVER_H
