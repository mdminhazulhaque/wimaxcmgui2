#include "scheduledialog.hpp"
#include "ui_scheduledialog.h"

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSchedule()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}

void ScheduleDialog::saveSchedule()
{
    // TODO
    close();
}
