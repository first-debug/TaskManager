#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(QWidget *parent, Task task) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog),
    m_currentTask(task)
{
    ui->setupUi(this);
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}
