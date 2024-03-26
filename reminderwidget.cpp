#include "reminderwidget.h"
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QMessageBox>

ReminderWidget::ReminderWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 时间编辑框
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm");
    timeEdit->setTime(QTime(20, 0)); // 设置初始时间为晚上八点
    layout->addWidget(timeEdit);

    // 启动定时提醒按钮
    pushButton = new QPushButton("该背单词啦！", this);
    layout->addWidget(pushButton);

    // 停止定时提醒按钮
    pushButton_2 = new QPushButton("OK", this);
    layout->addWidget(pushButton_2);

    // 连接按钮点击信号与槽函数
    connect(pushButton, &QPushButton::clicked, this, &ReminderWidget::startReminder);
    connect(pushButton_2, &QPushButton::clicked, this, &ReminderWidget::stopReminder);
}

void ReminderWidget::startReminder()
{
    // 获取设定的提醒时间
    QTime reminderTime = timeEdit->time();

    // 计算时间差，设置定时器
    int millisecondsToReminder = QTime::currentTime().msecsTo(reminderTime);
    if (millisecondsToReminder < 0)
    {
        millisecondsToReminder += 24 * 60 * 60 * 1000; // 如果提醒时间在当前时间之前，则将其设置到第二天同一时间
    }
    timerId = startTimer(millisecondsToReminder);
}

void ReminderWidget::stopReminder()
{
    if (timerId != 0)
    {
        killTimer(timerId); // 在 QWidget 上下文中调用 killTimer
        timerId = 0;
    }
}

void ReminderWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        // 在这里执行提醒操作，这里仅做示例，弹出一个对话框显示提醒信息
        QMessageBox::information(this, "提醒", "该背单词啦！");
    }
}
