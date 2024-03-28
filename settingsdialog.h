#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTime>
#include "DatabaseManager.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~SettingsDialog();

signals:
    void reminderTimeUpdated(const QTime& time);
    void reminderStateChanged(bool enabled); // 当复选框的选中状态变化时发射

private slots:
    void on_saveButton_clicked(); // 用户点击保存按钮时触发
    void onReminderCheckBoxToggled(bool checked); // 定时提醒功能开关

private:
    Ui::SettingsDialog *ui;
    DatabaseManager *dbManager; // 指向DatabaseManager的指针

    void updateWordCounts();
};

#endif // SETTINGSDIALOG_H
