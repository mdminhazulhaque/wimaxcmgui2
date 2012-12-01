#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>

namespace Ui {
class ScheduleDialog;
}

class ScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleDialog(QWidget *parent = 0);
    ~ScheduleDialog();

public slots:
    void saveSchedule();

private:
    Ui::ScheduleDialog *ui;
};

#endif // SCHEDULEDIALOG_H
