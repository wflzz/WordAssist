#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DatabaseManager.h"
#include <QTimeEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rememberedButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager *dbManager;
    QString currentWord;

    void showRandomWord();


    void timerEvent(QTimerEvent *event) override;
    void startReminder();
    void stopReminder();
    QTimeEdit *timeEdit;
    int timerId = 0;
};

#endif // MAINWINDOW_H
