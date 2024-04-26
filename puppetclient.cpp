#include "puppetclient.h"
#include <QBoxLayout>
#include <QDebug>

PuppetClient::PuppetClient()
{
    setFixedSize(250, 100);
    show();
    auto widget = new QWidget();
    auto layout = new QGridLayout(widget);
    setLayout(layout);

    auto connectCheckBox = new QCheckBox("Connect");
    _run = new QCheckBox("Run");
    _statusLabel = new QLabel("Disconnected!");
    _status = DISCONNECTED;

    _run->setEnabled(false);

    connect(connectCheckBox, &QCheckBox::toggled, this, [this](auto checked) {
        _run->setEnabled(checked);
        if (!checked) {
            _run->setChecked(false);
        }
        emit connectRequest(checked);
    });

    connect(_run, &QCheckBox::toggled, this, [this](auto checked) {
        if (checked) {
            if (_runningRequest = _server->startRunning()) {
                _statusLabel->setText("Running!");
                _status = RUNNING;
            } else {
                _statusLabel->setText("<b>Pending!</b>");
                _status = PENDING;
            }
        } else {
            if (_status != PENDING) {
                _runningRequest = !_server->stopRunning();
                _statusLabel->setText("Connected!");
                _status = CONNECTED;
            } else {
                _statusLabel->setText("Connected!");
                _status = CONNECTED;
            }
        }
    });

    layout->addWidget(connectCheckBox);
    layout->addWidget(_run);
    layout->addWidget(_statusLabel);
}

void PuppetClient::setServer(IServer *server)
{
    if (!server) {
        _statusLabel->setText("<b>Disconnected!</b>");
        _status = DISCONNECTED;
    } else {
        _statusLabel->setText("Connected!");
        _status = CONNECTED;
    }
    _server = server;
}

void PuppetClient::updateEvent(bool canRun)
{
    if (!canRun) {
        return;
    }

    if (!_run->isChecked()) {
        _statusLabel->setText("IDC");
        return;
    }

    if (_status == PENDING) {
        _server->startRunning();
        _statusLabel->setText("Running!");
        _status = RUNNING;
    }
}
