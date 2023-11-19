#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "ui_ToDo.h"
#include <QtWidgets/QListWidget>
#include <QtCore/QString>
#include "Task.h"
#include <QtWidgets/QComboBox>


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
    void searchTask();
    
  
    
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
    QLineEdit* searchedTask;
    QPushButton* searchButton;
    
    
};
