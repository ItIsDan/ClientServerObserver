#ifndef PUPPETCLIENT_H
#define PUPPETCLIENT_H

#include <QWidget>
#include "puppetserver.h"
#include <QLabel>

class PuppetClient : public QWidget
{
    Q_OBJECT
public:
    PuppetClient();

    void setServer(PuppetServer *server);
    PuppetServer *_server;
    bool _running { false };

private:
    QLabel *_status;

signals:
    void disconnectRequest();
    void connectRequest(bool);
};

#endif // PUPPETCLIENT_H
