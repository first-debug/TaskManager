#include <QDebug>

#include "taskdb.h"

TaskDB::TaskDB()
{ }

TaskDB::~TaskDB()
{
    if (!m_db.isOpen())
        m_db.close();
}

bool TaskDB::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("task.db");

    if (!m_db.open()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключться к БД!");
        return false;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "text TEXT NOT NULL,"
                    "description TEXT,"
                    "deadline TEXT,"
                    "priority TEXT,"
                    "status TEXT," // Active, Complited
                    "tags TEXT)"
                    )) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось создать таблицу\nПричина:"
                              + m_db.lastError().text());
        return false;
    }
    return true;
}

void TaskDB::loadTasks(QList<Task>& tasks, QString priorityFilter, QString sortColumn, QString tags)
{
    tasks.clear();

    QString request = "SELECT * FROM tasks ";
    if (!priorityFilter.isEmpty())
        request += "WHERE priority='" + priorityFilter + "' ";
    if (!tags.isEmpty()) {
        if (!priorityFilter.isEmpty())
            request += "AND ";
        else
            request += "WHERE ";
        request += "tags LIKE '%"+ tags + "%' ";
    }
    request += "ORDER BY status";
    if (!sortColumn.isEmpty())
        request += ", " + sortColumn;

    QSqlQuery query(request);

    while (query.next()) {
        int id = query.value(0).toInt();
        QString text = query.value(1).toString();
        QString description = query.value(2).toString();
        QString deadline = query.value(3).toString();
        QString priority = query.value(4).toString();
        QString status = query.value(5).toString();
        QStringList tags = query.value(6).toString().split(',');
        tasks.append(Task(id, text, description, deadline, priority, status, tags));
    }
    if (query.lastError().type() != QSqlError::NoError)
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось загрузить список задач!");
}

bool TaskDB::addTask(const Task& task)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tasks "
                  "(text, description, deadline, priority, status, tags) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(task.text);
    query.addBindValue(task.description);
    query.addBindValue(task.deadline);
    query.addBindValue(task.priority);
    query.addBindValue(task.status);
    query.addBindValue(task.tags.join(','));
    query.exec();

    if (query.lastError().type() != QSqlError::NoError)
        return false;
    return true;
}

bool TaskDB::updateTask(const Task& task) {
    QSqlQuery query;
    query.prepare("UPDATE tasks SET text = ?, description = ?, deadline = ?, priority = ?, tags = ? "
                  "WHERE id = ?");
    query.addBindValue(task.text);
    query.addBindValue(task.description);
    query.addBindValue(task.deadline);
    query.addBindValue(task.priority);
    query.addBindValue(task.tags.join(','));
    query.addBindValue(task.id);
    query.exec();
    if (query.lastError().type() != QSqlError::NoError)
        return false;
    return true;
}

bool TaskDB::removeTaskById(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id=?");
    query.addBindValue(id);
    query.exec();

    if (query.lastError().type() != QSqlError::NoError)
        return false;
    return true;
}

bool TaskDB::markCompletedById(const int id)
{
    QSqlQuery query;
    query.prepare("UPDATE tasks SET status = 'Complited' WHERE id = ?");
    query.addBindValue(id);
    query.exec();

    if (query.lastError().type() != QSqlError::NoError)
        return false;
    return true;
}
