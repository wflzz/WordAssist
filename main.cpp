#include "mainwindow.h"
#include <QApplication>

// #include <QtSql/QSqlDatabase>
// #include <QtSql/QSqlQuery>
// #include <QDebug>
// #include <QtSql/QSqlError>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // // 连接到SQLite数据库
    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("wordlist.db"); // 数据库文件名
    // if (!db.open()) {
    //     qDebug() << "无法打开数据库：" << db.lastError();
    //     return -1;
    // }

    // // 创建一个表
    // QSqlQuery query;
    // bool success = query.exec("CREATE TABLE IF NOT EXISTS words ("
    //                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                           "word TEXT NOT NULL, "
    //                           "translation TEXT NOT NULL, "
    //                           "remembered INTEGER NOT NULL DEFAULT 0)");
    // if (!success) {
    //     qDebug() << "无法创建表：" << query.lastError();
    //     return -1;
    // }

    MainWindow w;
    w.show();
    return a.exec();
}
