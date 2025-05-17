#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>

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
    void removeTask();

private:
    Ui::MainWindow *ui;
    TaskDB taskDB;
    QList<Task> tasks;

    void loadTasks();
};

#endif // MAINWINDOW_H
