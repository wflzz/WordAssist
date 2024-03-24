#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(new DatabaseManager(QDir::currentPath() + "/../WordAssist/wordlist.db"))
{
    ui->setupUi(this);
    showRandomWord();
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
