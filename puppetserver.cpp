#include "puppetserver.h"
#include <QVBoxLayout>
#include <QCheckBox>

PuppetServer::PuppetServer(QWidget *parent) : QWidget(parent)
{
    setFixedSize(250, 100);
    show();
    setWindowTitle("Server");
    auto widget = new QWidget();
    auto layout = new QGridLayout(widget);
    auto maxSizeLabel = new QLabel("Max Runs: ");
    maxRuns = new QLabel(QString::number(_maxRuns));
    auto currentSizeLabel = new QLabel("Current Runs Count: ");
    currentRuns = new QLabel(QString::number(_currentRunsCount));

    layout->addWidget(maxSizeLabel);
    layout->addWidget(maxRuns);
    layout->addWidget(currentSizeLabel);
    layout->addWidget(currentRuns);

    setLayout(layout);
}

void PuppetServer::start(int maxRuns)
{
    _maxRuns = maxRuns;
}

bool PuppetServer::startRunning()
{
    if (_currentRunsCount >= _maxRuns) {
        return false;
    }

    ++_currentRunsCount;

    currentRuns->setText(QString::number(_currentRunsCount));

    return true;
}

bool PuppetServer::stopRunning()
{
    if (_currentRunsCount <= 0)
        return false;

    --_currentRunsCount;

    currentRuns->setText(QString::number(_currentRunsCount));

    return true;
}

PuppetServer::~PuppetServer()
{}
