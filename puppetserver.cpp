#include "puppetserver.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>

PuppetServer::PuppetServer()
{
    setFixedSize(250, 100);
    show();
    setWindowTitle("Server");
    auto widget = new QWidget();
    auto layout = new QGridLayout(widget);
    auto maxSizeLabel = new QLabel("Max Runs: ");
    maxRunsLabel = new QLabel(QString::number(_maxRuns));
    auto currentSizeLabel = new QLabel("Current Runs Count: ");
    currentRuns = new QLabel(QString::number(_currentRunsCount));

    layout->addWidget(maxSizeLabel);
    layout->addWidget(maxRunsLabel);
    layout->addWidget(currentSizeLabel);
    layout->addWidget(currentRuns);

    setLayout(layout);
}

void PuppetServer::start(int maxRuns)
{
    _maxRuns = maxRuns;
    maxRunsLabel->setText(QString::number(_maxRuns));
}

bool PuppetServer::startRunning()
{
    if (_currentRunsCount >= _maxRuns) {
        return false;
    }

    ++_currentRunsCount;

    currentRuns->setText(QString::number(_currentRunsCount));

    //    notify(_currentRunsCount < _maxRuns);

    return true;
}

bool PuppetServer::stopRunning()
{
    if (_currentRunsCount <= 0)
        return true;

    --_currentRunsCount;

    currentRuns->setText(QString::number(_currentRunsCount));

    notify(_currentRunsCount < _maxRuns);

    return false;
}

void PuppetServer::attach(IObserver *observer) noexcept
{
    for (auto &obs : _observers)
        if (obs == observer)
            return;

    _observers.push_back(observer);
}

void PuppetServer::detach(IObserver *observer) noexcept
{
    _observers.removeOne(observer);
}

void PuppetServer::notify(bool canRun) noexcept
{
    for (auto &obs : _observers) {
        obs->updateEvent(canRun);
    }
}

PuppetServer::~PuppetServer()
{}
