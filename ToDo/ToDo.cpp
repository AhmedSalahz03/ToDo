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

    connect(addNewTaskBtn, SIGNAL(clicked()), this, SLOT(addNewTask()));

    listWidget = new QListWidget(this);
    listWidget->move(300, 300);
    listWidget->resize(300, 200);
}

ToDo::~ToDo()
{}

void ToDo::addNewTask() {

    name = new QLineEdit(this);
    name->move(300, 150);
    name->resize(130, 30);// Adjust position as needed
    name->show();

    doneButton = new QPushButton(this);
    doneButton->setText("Done");
    doneButton->move(300, 200); 
    doneButton->resize(100, 50);// Adjust position as needed

    connect(doneButton, SIGNAL(clicked()), this, SLOT(createTask()));

    doneButton->show();
}

void ToDo::createTask() {

    std::string taskName = name->text().toStdString();

    Task newTask(taskName);

    tasks.push_back(newTask);

    updateUI();

    delete name;  // Delete the QLineEdit
    delete doneButton;  // Delete the QPushButton
}

void ToDo::updateUI() {

    listWidget->clear();

    for (const Task& task : tasks) {
        
        new QListWidgetItem(QString::fromStdString(task.name), listWidget);
    }
}

