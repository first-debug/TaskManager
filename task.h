#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QStringList>

class Task
{
public:
    Task(const int id = -1,
         const QString& text = "",
         const QString& description = "",
         const QString& deadline = "",
         const QString& priority = "Средний",
         const QString& status = "Active",
         const QStringList& tags = QStringList())
        : id(id), text(text), description(description),
          deadline(deadline), priority(priority), status(status), tags(tags)
    { }

    int id;
    QString text;
    QString description;
    QString deadline; // Формат "dd.MM.yyyy hh:mm"
    QString priority;
    QString status; // Active, Complited
    QStringList tags;
};

#endif // TASK_H
