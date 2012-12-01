#include "keyboarddialog.hpp"
#include "ui_keyboarddialog.h"

KeyboardDialog::KeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

KeyboardDialog::~KeyboardDialog()
{
    delete ui;
}
