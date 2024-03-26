#ifndef REMINDERWIDGET_H
#define REMINDERWIDGET_H

#include <QWidget>
#include <QTimeEdit>
#include <QPushButton>

class ReminderWidget : public QWidget
{
    Q_OBJECT

public:
    ReminderWidget(QWidget *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void startReminder();
    void stopReminder();

private:
    QTimeEdit *timeEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    int timerId = 0;
};

#endif // REMINDERWIDGET_H
