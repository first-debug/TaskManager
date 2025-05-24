#ifndef TASKDB_H
#define TASKDB_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QComboBox>
#include <QLineEdit>

#include "task.h"

class TaskDB
{
public:
    TaskDB();
    ~TaskDB();

    bool init();
    void loadTasks(QList<Task>&, QString prority = "", QString sortParm = "", QString tags = "");
    bool addTask(const Task&);
    bool updateTask(const Task&);
    bool removeTaskById(const int);
    bool markCompletedById(const int);

private:
    QSqlDatabase m_db;
};

#endif // TASKDB_H
