#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "SettingsDialog.h" // 确保包括设置对话框的头文件
#include <QMessageBox>
#include "reminderdialog.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(new DatabaseManager(QDir::currentPath() + "/../WordAssist/wordlist.db")),
    reminderTimer(new QTimer(this)),
    settingsDialog(new SettingsDialog(dbManager, this))
{
    ui->setupUi(this);
    connect(ui->rememberButton, &QPushButton::clicked, this, &MainWindow::on_rememberButton_clicked);

    // 连接QToolButton的clicked信号到openSettingsDialog槽
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::openSettingsDialog);

    // 当定时器超时时显示提醒对话框
    connect(reminderTimer, &QTimer::timeout, this, &MainWindow::showReminderDialog);
    // 初始化定时提醒
    reminderTime = dbManager->getReminderTime(); // 这个方法返回提醒时间
    setupTimer();

    showRandomWord(); // 显示第一个单词

    connect(settingsDialog, &SettingsDialog::reminderStateChanged, this, &MainWindow::handleReminderStateChange);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_rememberButton_clicked() {
    if (dbManager->setWordRemembered(currentWordId)) { // 假设这个方法根据ID更新单词状态
        showRandomWord(); // 获取并显示下一个单词
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法更新单词状态。"));
    }
}

void MainWindow::showRandomWord() {
    auto wordData = dbManager->getRandomWord(); // 假设这返回一个包含ID和单词的结构或对
    currentWordId = wordData.id;
    ui->wordLabel->setText(wordData.word+" "+wordData.translation);
}

void MainWindow::updateReminderTime(const QTime& time) {
    reminderTime = time;
    setupTimer(); // 根据用户在设置对话框中设置的新时间更新定时器
}

void MainWindow::setupTimer() {
    // 将当前时间到提醒时间的时间差转换为毫秒
    int interval = QTime::currentTime().msecsTo(reminderTime);
    if (interval < 0) {
        interval += 24 * 60 * 60 * 1000; // 如果时间已过，设置为第二天的这个时间
    }

    reminderTimer->start(interval);
    reminderTimer->setSingleShot(true); // 设置定时器为单次触发
}

void MainWindow::openSettingsDialog() {
    connect(settingsDialog, &SettingsDialog::reminderTimeUpdated, this, &MainWindow::updateReminderTime);
    settingsDialog->exec(); // 显示设置对话框
}

// 显示提醒对话框
void MainWindow::showReminderDialog() {
    ReminderDialog *reminderDialog = new ReminderDialog(this);
    reminderDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保关闭时删除
    reminderDialog->show(); // 显示提醒对话框

    // 关闭时设置定时器以便下次提醒
    connect(reminderDialog, &QDialog::finished, this, &MainWindow::setupTimer);
}

void MainWindow::handleReminderStateChange(bool enabled) {
    if (enabled) {
        // 启动定时提醒
        setupTimer(/* 提醒时间 */);
    } else {
        // 停止定时提醒
        reminderTimer->stop();
    }
}
