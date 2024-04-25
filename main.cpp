#include "puppetserver.h"
#include "puppetclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto server = new PuppetServer;
    server->start(2);

    for (auto i = 1; i <= 3; ++i) {
        auto client = new PuppetClient;
        client->setWindowTitle(QString("Client %1").arg(i));
        QObject::connect(client, &PuppetClient::connectRequest, client,
                         [server, client](auto request) {
                             request ? server->attach(client) : server->detach(client);
                             request ? client->setServer(server) : client->setServer(nullptr);
                         });
    }

    return app.exec();
}
