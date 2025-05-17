#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>

#include "task.h"

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = nullptr, Task task = Task());
    ~NewTaskDialog();

    Task getTask() const;

private:
    Ui::NewTaskDialog *ui;
    Task m_currentTask;
};

#endif // NEWTASKDIALOG_H
