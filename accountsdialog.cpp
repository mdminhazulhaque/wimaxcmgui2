#include "accountsdialog.hpp"
#include "ui_accountsdialog.h"

AccountsDialog::AccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountsDialog)
{
    ui->setupUi(this);
    settings = new QSettings("mdminhazulhaque","wimaxcmgui");

    readSavedIdentities();

    connect(ui->bActivate, SIGNAL(clicked()), this, SLOT(activateIdentity()));
    connect(ui->bRemove, SIGNAL(clicked()), this, SLOT(removeIdentity()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveAccountDetails()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

AccountsDialog::~AccountsDialog()
{
    delete ui;
    delete settings;
}

void AccountsDialog::readSavedIdentities()
{
    for(int i=0;;i++)
    {
        QVariant value = settings->value(QString("user%1").arg(i));
        if(value.isValid())
        {
            userIdentity << value.toString();
            userPassword << settings->value(QString("pass%1").arg(i)).toString();
        }
        else
            break;
    }
    ui->EntryList->clear();
    ui->EntryList->addItems(userIdentity);
}

void AccountsDialog::writeSavedIdentities()
{
    settings->clear();
    for(int i=0;i<userIdentity.size();i++)
    {
        settings->setValue(QString("user%1").arg(i), userIdentity.at(i));
        settings->setValue(QString("pass%1").arg(i), userPassword.at(i));
    }
    ui->EntryList->clear();
    ui->EntryList->addItems(userIdentity);
}

void AccountsDialog::Show()
{
    ui->macaddress->setText(wcmRead("wimaxc versions | grep MAC | cut -d' ' -f3"));
    show();
}

void AccountsDialog::saveAccountDetails()
{
    if(ui->username->text().isEmpty() or ui->password->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!", "Fill all text area",QMessageBox::Ok);
        return;
    }
    else
    {
        QProcess::startDetached("wimaxc set UserIdentity "+ui->username->text());
        QProcess::startDetached("wimaxc set UserPassword "+ui->username->text());
        QProcess::startDetached("wimaxc options save");
        if(ui->isSave->isChecked())
        {
            userIdentity << ui->username->text();
            userPassword << ui->password->text();
            writeSavedIdentities();
        }
    }
    close();
}

void AccountsDialog::activateIdentity()
{
    QProcess::startDetached("wimaxc set UserIdentity "+userIdentity.at(ui->EntryList->currentIndex()));
    QProcess::startDetached("wimaxc set UserPassword "+userPassword.at(ui->EntryList->currentIndex()));
    QProcess::startDetached("wimaxc options save");
}

void AccountsDialog::removeIdentity()
{
    userIdentity.removeAt(ui->EntryList->currentIndex());
    userPassword.removeAt(ui->EntryList->currentIndex());
    writeSavedIdentities();
}

void AccountsDialog::autoSetIdentity()
{
    // wimaxc versions | grep MAC | cut -d' ' -f3
    /*
    QString mac = "b8-61-6f-02-05-d6";
    mac.remove("-");
    mac.remove(":");
    if(userMACAddress.indexOf(mac))
        qDebug() << "Found!";
    */

}
