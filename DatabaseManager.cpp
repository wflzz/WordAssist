#include "DatabaseManager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(const QString& path) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);

    if (!database.open()) {
        qDebug() << "Error: connection with database failed:" << database.lastError();
    }
}

DatabaseManager::~DatabaseManager() {
    if (database.isOpen()) {
        database.close();
    }
}

bool DatabaseManager::isOpen() const {
    return database.isOpen();
}

bool DatabaseManager::addWord(const QString& word, const QString& translation) {
    QSqlQuery query;
    query.prepare("INSERT INTO words (word, translation) VALUES (:word, :translation)");
    query.bindValue(":word", word);
    query.bindValue(":translation", translation);
    return query.exec();
}

WordData DatabaseManager::getRandomWord() {
    QSqlQuery query("SELECT id, word, translation FROM words WHERE remembered = 0 ORDER BY RANDOM() LIMIT 1");
    if (query.next()) {
        return {query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()};
    }
    return {}; // 返回一个空的结构体实例
}

bool DatabaseManager::setWordRemembered(int id) {
    QSqlQuery query;
    query.prepare("UPDATE words SET remembered = 1 WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

int DatabaseManager::getTotalWordsCount() {
    QSqlQuery query("SELECT COUNT(*) FROM words");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int DatabaseManager::getRememberedWordsCount() {
    QSqlQuery query("SELECT COUNT(*) FROM words WHERE remembered = 1");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QTime DatabaseManager::getReminderTime() {
    QSqlQuery query("SELECT value FROM settings WHERE key = 'reminderTime'");
    if (query.next()) {
        return QTime::fromString(query.value(0).toString(), "HH:mm");
    }
    return QTime(20, 0); // 默认提醒时间为20:00
}

void DatabaseManager::setReminderTime(const QTime& time) {
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO settings (key, value) VALUES ('reminderTime', :time)");
    query.bindValue(":time", time.toString("HH:mm"));
    query.exec();
}
