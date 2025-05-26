#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

#include "task.h"
#include "taskdb.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void editTask();
    void removeTask();
    void loadTasks();
    void markCompleted();

private:
    Ui::MainWindow *ui;
    TaskDB taskDB;
    QList<Task> tasks;

    void addTaskToUi(const Task&);
};

#endif // MAINWINDOW_H
