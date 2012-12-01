#ifndef WCMTIMER_HPP
#define WCMTIMER_HPP

#include <QTimer>

class WCMTimer : public QTimer
{
    Q_OBJECT
public:
    explicit WCMTimer(QObject *parent = 0);

public slots:
    void Start(int msec);
};

#endif // WCMTIMER_HPP
