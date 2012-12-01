#ifndef ACCOUNTSDIALOG_H
#define ACCOUNTSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include "wcmread.hpp"

namespace Ui {
class AccountsDialog;
}

class AccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountsDialog(QWidget *parent = 0);
    ~AccountsDialog();
    void readSavedIdentities();
    void writeSavedIdentities();
    //QString readCMD(QString command);

public slots:
    void Show();
    void saveAccountDetails();
    void activateIdentity();
    void removeIdentity();
    void autoSetIdentity();

private:
    Ui::AccountsDialog *ui;
    QSettings *settings;
    QStringList userIdentity, userPassword, userMACAddress;
};

#endif // ACCOUNTSDIALOG_H
