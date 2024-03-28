#ifndef REMINDERDIALOG_H
#define REMINDERDIALOG_H

#include <QDialog>

namespace Ui {
class ReminderDialog;
}

class ReminderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReminderDialog(QWidget *parent = nullptr);
    ~ReminderDialog();

private:
    Ui::ReminderDialog *ui;
};

#endif // REMINDERDIALOG_H
