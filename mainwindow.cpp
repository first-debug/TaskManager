#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!taskDB.init()) {
        return;
    }

    loadTasks();

    // Подключение сигналов и слотов
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadTasks() {
    tasks.clear();
    ui->taskList->clear();

    taskDB.loadTasks(tasks);

    for (const Task& task : tasks)
        ui->taskList->addItem(task.text);
}

void MainWindow::addTask() {
    QString text = ui->taskInput->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст задачи!");
        return;
    }

    Task newTask(-1, text);
    if (taskDB.addTask(newTask)) {
        loadTasks();
        ui->taskInput->clear();
    } else
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить задачу.");
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
