#include "taskwidgetitem.h"

TaskWidgetItem::TaskWidgetItem(const Task& task, QWidget *parent)
: QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5);

    // Название задачи
    taskNameLabel = new QLabel(task.text);
    taskNameLabel->setWordWrap(true);
    taskNameLabel->setMinimumWidth(this->width() * .10);
    taskNameLabel->setStyleSheet(" border: 1px solid #cccccc; border-radius: 5px");
    layout->addWidget(taskNameLabel, 1);

    // Описание задачи
    descriptionLabel = new QLabel(task.description);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setStyleSheet(" border: 1px solid #cccccc; border-radius: 5px");
    layout->addWidget(descriptionLabel, 2);

    // Дедлайн
    deadlineLabel = new QLabel(task.deadline);
    deadlineLabel->setStyleSheet(" border: 1px solid #cccccc; border-radius: 5px");
    layout->addWidget(deadlineLabel, 0);

    // Кнопка удаления
    deleteButton = new QPushButton(QString::fromUtf8("\xE2\x9C\x94"));
    deleteButton->setFixedSize(25, 25);
    deleteButton->setToolTip("Пометить, как выполненую");
    layout->addWidget(deleteButton, 0);
    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        this->setFocus();
        emit deleteRequested();
        this->setDisabled(true);
    });

    if (!QString::compare(task.status, "Complited", Qt::CaseInsensitive))
        this->setDisabled(true);
}

void TaskWidgetItem::resizeEvent(QResizeEvent*) {
    taskNameLabel->setMinimumWidth(this->width() * .10);
}
