#include "SettingsDialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(DatabaseManager *dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    dbManager(dbManager)
{
    ui->setupUi(this);
    // 加载当前提醒时间设置并显示在界面上
    QTime currentTime = dbManager->getReminderTime();
    ui->timeEdit->setTime(currentTime);
    ui->reminderCheckBox->setChecked(true); // 默认开启定时提醒功能

    updateWordCounts();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::on_saveButton_clicked);
    connect(ui->reminderCheckBox, &QCheckBox::toggled, this, &SettingsDialog::onReminderCheckBoxToggled);

}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::on_saveButton_clicked() {
    QTime newTime = ui->timeEdit->time();
    dbManager->setReminderTime(newTime); // 更新数据库中的提醒时间
    emit reminderTimeUpdated(newTime); // 发送信号，以便MainWindow可以更新定时器
    accept(); // 关闭对话框
}

void SettingsDialog::onReminderCheckBoxToggled(bool checked) {
    emit reminderStateChanged(checked);
}

void SettingsDialog::updateWordCounts() {
    int totalWords = dbManager->getTotalWordsCount();
    int rememberedWords = dbManager->getRememberedWordsCount();

    ui->totalWordsLabel->setText(QString("词库共 %1 个单词").arg(totalWords));
    ui->rememberedWordsLabel->setText(QString("你已经背了 %1 个").arg(rememberedWords));
}
