#ifndef TASKDB_H
#define TASKDB_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>

#include "task.h"

class TaskDB
{
public:
    TaskDB();
    ~TaskDB();

    bool init();
    void loadTasks(QList<Task>&);
    bool addTask(const Task&);
    bool removeTaskById(const int);

private:
    QSqlDatabase m_db;
};

#endif // TASKDB_H
