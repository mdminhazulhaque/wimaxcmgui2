#ifndef WCMREAD_HPP
#define WCMREAD_HPP

#include <QString>
#include <QProcess>
#include "defines.hpp"

static QString wcmRead(QString command)
{
    QProcess process;
    QStringList args;
    args << "-c" << command;
    process.start(SHELL, args);
    process.waitForFinished();
    return process.readLine().trimmed();
    process.close();
}

#endif // WCMREAD_HPP
