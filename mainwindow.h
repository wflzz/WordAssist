#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "DatabaseManager.h"
#include <QTime>
#include "SettingsDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rememberButton_clicked(); // 处理记住按钮点击事件
    void updateReminderTime(const QTime& time); // 更新定时提醒时间
    void showRandomWord(); // 显示随机单词
    void openSettingsDialog(); // 点击按钮：打开设置面板
    void handleReminderStateChange(bool enabled);

private:
    Ui::MainWindow *ui;
    DatabaseManager *dbManager; // 数据库管理器实例
    QTimer *reminderTimer; // 定时提醒的定时器
    int currentWordId; // 用于追踪当前单词的ID
    QTime reminderTime;
    SettingsDialog *settingsDialog;

    void setupTimer(); // 根据给定时间设置定时器
    void showReminderDialog();
};

#endif // MAINWINDOW_H
