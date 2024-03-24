#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>

class DatabaseManager {
public:
    explicit DatabaseManager(const QString& path);
    ~DatabaseManager();

    bool isOpen() const;
    bool addWord(const QString& word, const QString& translation);
    QString getRandomWord();
    bool setWordRemembered(const QString& word);

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
