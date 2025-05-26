#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>

#include "task.h"

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr, Task task = Task());
    ~TaskDialog();

    Task getTask() const;

private:
    Ui::TaskDialog *ui;
    Task m_currentTask;

private slots:
    void checkDeadlineInput();
};

#endif // TASKDIALOG_H
