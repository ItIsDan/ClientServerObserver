#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>

class PuppetServer : public QWidget
{
    Q_OBJECT

public:
    explicit PuppetServer(QWidget *parent = nullptr);
    void start(int maxRuns = 2);
    bool startRunning();
    bool stopRunning();
    virtual ~PuppetServer();

private:
    QLabel *maxRuns;
    QLabel *currentRuns;
    int _maxRuns { 2 };
    int _currentRunsCount { 0 };
};
#endif // WIDGET_H
