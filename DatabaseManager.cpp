#include "DatabaseManager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(const QString& path) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);

    if (!database.open()) {
        qDebug() << "Error: connection with database failed:" << database.lastError().text();
    } else {
        qDebug() << "Database connected successfully.";
    }

    qDebug() << "Database path:" << database.databaseName();
    if(database.tables().contains("words")) {
        qDebug() << "The 'words' table exists.";
    } else {
        qDebug() << "The 'words' table does not exist.";
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

QString DatabaseManager::getRandomWord() {
    QSqlQuery query("SELECT word, translation FROM words ORDER BY RANDOM() LIMIT 1");
    if (query.next()) {
        return query.value(0).toString() + " - " + query.value(1).toString();
    } else {
        qDebug() << "getRandomWord error:" << query.lastError().text();
        return QString();
    }
}

bool DatabaseManager::setWordRemembered(const QString& word) {
    QSqlQuery query;
    query.prepare("UPDATE words SET remembered = 1 WHERE word = :word");
    query.bindValue(":word", word);
    return query.exec();
}
