#include "puppetclient.h"
#include <QBoxLayout>
#include <QCheckBox>
#include <QTimer>
#include <QDebug>

PuppetClient::PuppetClient()
{
    setFixedSize(250, 100);
    show();
    auto widget = new QWidget();
    auto layout = new QGridLayout(widget);
    setLayout(layout);

    auto timer = new QTimer();
    auto connectCheckBox = new QCheckBox("Connect");
    auto run = new QCheckBox("Run");
    _status = new QLabel("Disconnected!");

    timer->setInterval(250);
    run->setEnabled(false);
    connect(connectCheckBox, &QCheckBox::toggled, this, [this, run](auto checked) {
        run->setEnabled(checked);
        if (!checked)
            run->setChecked(false);
        emit connectRequest(checked);
    });
    connect(run, &QCheckBox::toggled, this, [this, timer](auto checked) {
        if (checked) {
            timer->start();
            _status->setText("Starting run...");
        } else {
            timer->stop();
            _status->setText("Connected!");
            if (_running) {
                _server->stopRunning();
            }
        }
    });

    connect(timer, &QTimer::timeout, this, [this, timer] {
        if (_server) {
            qInfo() << "ping as" << windowTitle();
            if (_running = _server->startRunning()) {
                _status->setText("Running!");
                timer->stop();
            }
        }
    });

    layout->addWidget(connectCheckBox);
    layout->addWidget(run);
    layout->addWidget(_status);
}

void PuppetClient::setServer(PuppetServer *server)
{
    !server ? _status->setText("Disconnected!") : _status->setText("Connected!");
    _server = server;
}
