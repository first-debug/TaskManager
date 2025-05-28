#include "mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "taskdialog.h"
#include "taskwidgetitem.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!taskDB.init()) {
        return;
    }

    ui->sortComboBox->addItems({"По дедлайну", "По приоритету", "По алфавиту"});

    ui->filterPriority->addItems({"Нет", "Высокий", "Средний", "Низкий"});

    loadTasks();

    // Подключение сигналов и слотов
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::editTask);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
    connect(ui->filterPriority, &QComboBox::activated, this, &MainWindow::loadTasks);
    connect(ui->sortComboBox, &QComboBox::activated, this, &MainWindow::loadTasks);
    connect(ui->filterTags, &QLineEdit::textEdited, this, &MainWindow::loadTasks);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadTasks() {
    QString priorityExpression = "";
    if (ui->filterPriority->currentIndex() != 0)
        priorityExpression = ui->filterPriority->currentText();

    QString sortColumn = "deadline";
    if (ui->sortComboBox->currentIndex() == 1)
        sortColumn = "priority";
    else if (ui->sortComboBox->currentIndex() == 2)
        sortColumn = "text";

    QString tagsExpression = "";
    if (!ui->filterTags->text().isEmpty())
        tagsExpression = ui->filterTags->text();

    tasks.clear();
    ui->taskList->clear();

    taskDB.loadTasks(tasks, priorityExpression, sortColumn, tagsExpression);

    for (const Task& task : tasks)
        addTaskToUi(task);
}

void MainWindow::addTask() {
    TaskDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        Task newTask = dialog.getTask();

        if (taskDB.addTask(newTask))
            loadTasks();
        else
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить задачу.");
        }
    }

void MainWindow::editTask() {
    int row = ui->taskList->currentIndex().row();
    Task taskToEdit = tasks[row];
    TaskDialog dialog(this, &taskToEdit);

    if (dialog.exec() == QDialog::Accepted) {
        Task newTask = dialog.getTask();

        if (taskDB.updateTask(newTask))
            loadTasks();
        else
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить задачу.");
    }
}

void MainWindow::removeTask() {
    QListWidgetItem* item = ui->taskList->currentItem();
    if (!item) return;

    int row = ui->taskList->row(item);
    Task taskToRemove = tasks[row];

    if (taskDB.removeTaskById(taskToRemove.id)) {
        tasks.removeAt(row);
        delete item;
    } else
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить задачу!");
}

void MainWindow::addTaskToUi(const Task& task) {
    TaskWidgetItem *itemWidget = new TaskWidgetItem(task);
    QListWidgetItem *listItem = new QListWidgetItem(ui->taskList);
    listItem->setSizeHint(itemWidget->sizeHint());
    ui->taskList->setItemWidget(listItem, itemWidget);
    connect(itemWidget, &TaskWidgetItem::deleteRequested, this, &MainWindow::markCompleted);
}

void MainWindow::markCompleted() {
    QListWidgetItem* item = ui->taskList->currentItem();
    if (!item) return;

    int row = ui->taskList->row(item);
    Task taskToMark = tasks[row];
    if (!taskDB.markCompletedById(taskToMark.id))
        QMessageBox::warning(this, "Ошибка", "Не удалось отметиить задачу выполненной!");

    loadTasks();
}
