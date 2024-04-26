#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include "IServer.h"

class PuppetServer : public IServer
{
    Q_OBJECT

public:
    explicit PuppetServer();
    void start(int maxRuns);
    bool startRunning();
    bool stopRunning();
    void attach(IObserver *observer) noexcept override;
    void detach(IObserver *observer) noexcept override;
    void notify(bool canConnect) noexcept;

    virtual ~PuppetServer();

private:
    QVector<IObserver *> _observers;
    QLabel *maxRunsLabel;
    QLabel *currentRuns;
    int _maxRuns { 2 };
    int _currentRunsCount { 0 };
};
#endif // WIDGET_H
