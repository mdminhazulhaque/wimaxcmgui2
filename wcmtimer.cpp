#include "wcmtimer.hpp"

WCMTimer::WCMTimer(QObject *parent) : QTimer(parent) {}

void WCMTimer::Start(int msec)
{
    timeout();
    start(msec);
}
