#ifndef KEYBOARDDIALOG_HPP
#define KEYBOARDDIALOG_HPP

#include <QDialog>

namespace Ui {
class KeyboardDialog;
}

class KeyboardDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit KeyboardDialog(QWidget *parent = 0);
    ~KeyboardDialog();
    
private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_HPP
