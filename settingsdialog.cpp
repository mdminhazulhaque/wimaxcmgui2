#include "settingsdialog.hpp"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    if(QFile(QDir::homePath()+"/.config/autostart/wimaxcmgui.desktop").exists())
        ui->isAutostart->setChecked(1);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::saveSettings()
{
    if(ui->isAutostart->isChecked())
        QProcess::startDetached("/bin/cp /usr/share/applications/wimaxcmgui.desktop "
                                + QDir::homePath()
                                + "/.config/autostart/");
    else
        QProcess::startDetached("/bin/rm "
                                +QDir::homePath()
                                +"/.config/autostart/wimaxcmgui.desktop");
    close();
}
