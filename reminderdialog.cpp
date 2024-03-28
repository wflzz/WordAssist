#include "reminderdialog.h"
#include "ui_reminderdialog.h"

ReminderDialog::ReminderDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReminderDialog)
{
    ui->setupUi(this);
    ui->label->setText("It's time to learn some new words!");
}

ReminderDialog::~ReminderDialog()
{
    delete ui;
}
