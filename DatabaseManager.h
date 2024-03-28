#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QTimer>
#include <QTime>
#include <QString>

struct WordData {
    int id;
    QString word;
    QString translation;
};

class DatabaseManager {
public:
    explicit DatabaseManager(const QString& path);
    ~DatabaseManager();

    bool isOpen() const;
    bool addWord(const QString& word, const QString& translation);
    WordData getRandomWord();
    bool setWordRemembered(int id);
    int getTotalWordsCount();
    int getRememberedWordsCount();
    QTime getReminderTime();
    void setReminderTime(const QTime& time);

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
