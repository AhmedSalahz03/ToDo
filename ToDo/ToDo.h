#pragma once

#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include "ui_ToDo.h"
#include "Task.h"
#include "qcombobox.h"


class HashMap;

class ToDo : public QMainWindow
{
    Q_OBJECT

public:
    ToDo(QWidget* parent = nullptr);
    ~ToDo();

public slots:
    
    void createTask();
    void updateUI();
    void deleteTask();
  
    
private:
    

    Ui::ToDoClass ui;
    HashMap* tasks;
    QLineEdit* name;
    QPushButton* doneButton;
    QPushButton* deleteBtn;
    QComboBox* priority;
    QListWidget* allTasks;
    QListWidget* completeTasks;
    QListWidget* incompleteTasks;
    
};
