#ifndef PUPPETCLIENT_H
#define PUPPETCLIENT_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>

#include "IObserver.h"
#include "IServer.h"

enum Status
{
    DISCONNECTED,
    CONNECTED,
    PENDING,
    RUNNING,
    ERROR
};

class PuppetClient : public IObserver
{
    Q_OBJECT
public:
    PuppetClient();

    void setServer(IServer *server);
    void updateEvent(bool canConnect) override;

private:
    bool _runningRequest { false };
    IServer *_server;
    Status _status;
    QLabel *_statusLabel;
    QCheckBox *_run;

signals:
    void disconnectRequest();
    void connectRequest(bool);
};

#endif // PUPPETCLIENT_H
