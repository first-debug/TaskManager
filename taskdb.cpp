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
                    "deadline TEXT)"
                    )) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось создать таблицу\nПричина:"
                              + m_db.lastError().text());
        return false;
    }
    return true;
}

void TaskDB::loadTasks(QList<Task>& tasks)
{
    tasks.clear();

    QSqlQuery query("SELECT id, text, deadline FROM tasks");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString text = query.value(1).toString();
        QString deadline = query.value(2).toString();
        tasks.append(Task(id, text, deadline));
    }
}

bool TaskDB::addTask(const Task& task)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (text, deadline) VALUES (?, ?)");
    query.addBindValue(task.text);
    query.addBindValue(task.deadline);
    return query.exec();
}

bool TaskDB::removeTaskById(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id=?");
    query.addBindValue(id);
    return query.exec();
}
