#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDir>
#include <QTimerEvent>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(new DatabaseManager(QDir::currentPath() + "/../WordAssist/wordlist.db"))
{
    ui->setupUi(this);
    showRandomWord();





    QVBoxLayout *layout = new QVBoxLayout(this);

    // 时间编辑框
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm");
    timeEdit->setTime(QTime(2, 46)); // 设置初始时间为晚上八点
    layout->addWidget(timeEdit);

    startReminder();
}

MainWindow::~MainWindow() {
    delete ui;
    delete dbManager;
}

void MainWindow::on_rememberedButton_clicked() {
    dbManager->setWordRemembered(currentWord);
    showRandomWord();
}

void MainWindow::showRandomWord() {
    QString wordAndTranslation = dbManager->getRandomWord();
    currentWord = wordAndTranslation.split(" - ").first();
    ui->wordLabel->setText(wordAndTranslation);
}





void MainWindow::startReminder()
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


void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        // 在这里执行提醒操作，这里仅做示例，弹出一个对话框显示提醒信息
        QMessageBox::information(this, "提醒", "该背单词啦！");
    }
}

