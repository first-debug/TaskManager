#ifndef TASKWIDGETITEM_H
#define TASKWIDGETITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QMouseEvent>
#include "task.h"

class TaskWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidgetItem(const Task&, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    QLabel *taskNameLabel;
    QLabel *descriptionLabel;
    QLabel *deadlineLabel;
    QPushButton *deleteButton;

signals:
    void deleteRequested();
};

#endif // TASKWIDGETITEM_H
