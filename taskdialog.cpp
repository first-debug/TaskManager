#include <QDebug>
#include <QMessageBox>

#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent, Task* task) :
    QDialog(parent),
    ui(new Ui::TaskDialog),
    m_currentTask(*task)
{
    ui->setupUi(this);

    ui->priorityComboBox->addItems({"Высокий", "Средний", "Низкий"});
    ui->priorityComboBox->setCurrentIndex(1);
    ui->dueDateEdit->setMinimumDateTime(QDateTime::currentDateTime());

    if (m_currentTask.id != -1) {
        ui->taskName->setText(m_currentTask.text);
        ui->taskDescription->setText(m_currentTask.description);
        ui->dueDateEdit->setDateTime(QDateTime::fromString(m_currentTask.deadline, "dd.MM.yyyy hh.mm"));
        ui->priorityComboBox->setCurrentText(m_currentTask.priority);
        ui->tagsLineEdit->setText(m_currentTask.tags.join(", "));
    } else {
        ui->dueDateEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
    }
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        if (ui->taskName->text().isEmpty()){
            QMessageBox::warning(this, "Ошибка", "Нужно ввести название!");
            return;
        }
        accept();
    });
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->dueDateEdit, &QDateTimeEdit::dateTimeChanged, this, &TaskDialog::checkDeadlineInput);

    delete task;
}

Task TaskDialog::getTask() const
{
    Task task;
    task.id = m_currentTask.id;
    task.text = ui->taskName->text();
    task.description = ui->taskDescription->toPlainText();
    task.deadline = ui->dueDateEdit->dateTime().toString("dd.MM.yyyy hh.mm");
    task.priority = ui->priorityComboBox->currentText();
    for (QString &str : ui->tagsLineEdit->text().split(','))
        task.tags.append(str.trimmed());
    return task;
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

void TaskDialog::checkDeadlineInput() {
    if (ui->dueDateEdit->dateTime() <= QDateTime::currentDateTime())
        QMessageBox::warning(this, "Ошибка", "Неверное время для дедлайна!");
}
