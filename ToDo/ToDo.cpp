#include "ToDo.h"
#include <QPushButton>
#include <QLabel>
#include <qcheckbox.h>

ToDo::ToDo(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QPushButton* addNewTaskBtn = new QPushButton(this);
    addNewTaskBtn->setText("Add New Task");
    addNewTaskBtn->move(300, 100);
    addNewTaskBtn->resize(250, 30);

    QLabel* label = new QLabel(this);
    label->setText("All Tasks");
    label->move(300, 270);

    QLabel* label2 = new QLabel(this);
    label2->setText("Completed Tasks");
    label2->move(650, 270);
    
    
    

    connect(addNewTaskBtn, SIGNAL(clicked()), this, SLOT(addNewTask()));

    listWidget = new QListWidget(this);
    listWidget->move(300, 300);
    listWidget->resize(300, 350);

    completedTasks = new QListWidget(this);
    completedTasks->move(650, 300);
    completedTasks->resize(300, 350);
}

ToDo::~ToDo()
{}

void ToDo::addNewTask() {

    name = new QLineEdit(this);
    name->move(300, 150);
    name->resize(250, 40);
    name->show();

    doneButton = new QPushButton(this);
    doneButton->setText("Add");
    doneButton->move(375, 200); 
    doneButton->resize(100, 50);

    connect(doneButton, SIGNAL(clicked()), this, SLOT(createTask()));

    doneButton->show();
}

void ToDo::createTask() {

    std::string taskName = name->text().toStdString();
    Task newTask(taskName);
    tasks.insert(1, taskName);
   // tasks.push_back(newTask);
    name->clear();
    updateUI();

    delete name;  
    delete doneButton;  
}

void ToDo::updateUI() {
    tasks.updateUI(listWidget);
    /*
    listWidget->clear();
    completedTasks->clear();

    for (int i = 0; i < tasks.size(); i++) {
        QListWidgetItem* item = new QListWidgetItem(listWidget);
        item->setText(QString::fromStdString(tasks[i].name));

       
        QCheckBox* checkBox = new QCheckBox(listWidget);
        checkBox->setChecked(tasks[i].done);
        listWidget->setItemWidget(item, checkBox);

        connect(checkBox, &QCheckBox::stateChanged, this, &ToDo::updateUI);
        connect(checkBox, &QCheckBox::stateChanged, [i, this](int state) {
            tasks[i].done = (state == Qt::Checked);
            });
    }
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].done == 1) {
            QListWidgetItem* item = new QListWidgetItem(completedTasks);
            item->setText(QString::fromStdString(tasks[i].name));


            QCheckBox* checkBox = new QCheckBox(completedTasks);
            checkBox->setChecked(tasks[i].done);
            completedTasks->setItemWidget(item, checkBox);

            connect(checkBox, &QCheckBox::stateChanged, this, &ToDo::updateUI);
            connect(checkBox, &QCheckBox::stateChanged, [i, this](int state) {
                tasks[i].done = (state == Qt::Checked);
                });
        }
    }
    */
}

