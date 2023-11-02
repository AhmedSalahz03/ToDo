#pragma once

#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include "ui_ToDo.h"
#include "Task.h"

class ToDo : public QMainWindow
{
    Q_OBJECT

public:
    ToDo(QWidget* parent = nullptr);
    ~ToDo();

private slots:
    void addNewTask();
    void createTask();

private:
    void updateUI();

    Ui::ToDoClass ui;
    std::vector<Task> tasks;
    QLineEdit* name;
    QPushButton* doneButton;
    QListWidget* listWidget;
};
