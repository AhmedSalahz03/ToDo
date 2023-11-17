#include "ToDo.h"
#include "Hashmap.h"
#include <QPushButton>
#include <QLabel>
#include <qcheckbox.h>
#include "Hashmap.h"
#include <qcombobox.h>
#include <QString>
#include <string>

ToDo::ToDo(QWidget* parent)
    : QMainWindow(parent), tasks(new HashMap())
{
    ui.setupUi(this);

    QPushButton* addNewTaskBtn = new QPushButton(this);
    addNewTaskBtn->setText("Add New Task");
    addNewTaskBtn->move(300, 100);
    addNewTaskBtn->resize(250, 30);

    QLabel* allTasksLabel = new QLabel(this);
    allTasksLabel->setText("All Tasks");
    allTasksLabel->resize(150, 20);
    allTasksLabel->move(100, 270);
    QFont font = allTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    allTasksLabel->setFont(font);

    QLabel* completeTasksLabel = new QLabel(this);
    completeTasksLabel->setText("Complete Tasks");
    completeTasksLabel->resize(250, 20);
    completeTasksLabel->move(800, 270);
    font = completeTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    completeTasksLabel->setFont(font);

    QLabel* incompleteTasksLabel = new QLabel(this);
    incompleteTasksLabel->setText("Incomplete Tasks");
    incompleteTasksLabel->resize(250,20);
    incompleteTasksLabel->move(450, 270);
    font = incompleteTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    incompleteTasksLabel->setFont(font);
    
    connect(addNewTaskBtn, SIGNAL(clicked()), this, SLOT(addNewTask()));

    allTasks = new QListWidget(this);
    allTasks->move(100, 300);
    allTasks->resize(300, 450);

    QListWidgetItem* selectedItem = allTasks->currentItem();
    

    completeTasks = new QListWidget(this);
    completeTasks->move(800, 300);
    completeTasks->resize(300, 450);

    incompleteTasks = new QListWidget(this);
    incompleteTasks->move(450, 300);
    incompleteTasks->resize(300, 450);

    testWidget = new QListWidget(this);
    testWidget->move(1200, 300);
    testWidget->resize(300, 450);

    deleteBtn = new QPushButton(this);
    deleteBtn->setText("Delete Task");
    deleteBtn->move(850, 200);

    //connect(deleteBtn, &QPushButton::clicked, this, &ToDo::deleteTask(headValue));
    connect(deleteBtn, &QPushButton::clicked, [=]() {
        //Call the ToDo::deleteTask() function with the 'headValue' parameter
        deleteTask(selectedItem);
        });
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

    priority = new QComboBox(this);
    priority->move(500, 200);
    priority->setPlaceholderText("Priority");
    priority->addItem("1");
    priority->addItem("2");
    priority->addItem("3");
    priority->addItem("4");
    priority->addItem("5");

    connect(doneButton, SIGNAL(clicked()), this, SLOT(createTask()));

    doneButton->show();
    priority->show();
}

void ToDo::createTask() {
    int selectedPriority = priority->currentIndex() + 1;
    std::string taskName = name->text().toStdString();
    Task newTask(taskName);
    tasks->insert(selectedPriority, taskName);
    // tasks.push_back(newTask);
    name->clear();
    updateUI();

    delete name;  
    delete doneButton;  
    delete priority;

}

void ToDo::updateUI() {
    tasks->display(allTasks, *this, completeTasks, incompleteTasks, testWidget);
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
void ToDo::deleteTask(QListWidgetItem* selectedItem) {
    if (!selectedItem) {
        qDebug() << "No selected item!";
        return;
    }

    QString itemText = selectedItem->text();
    QStringList parts = itemText.split("    Priorty: ");
    if (parts.size() < 1) {
        qDebug() << "Separator not found or unexpected format!";
        return;
    }

    QString headValue = parts[0].trimmed();
    std::string str = headValue.toStdString();
    qDebug() << "Deleting string: " << str.c_str(); // Output for debugging

    tasks->deleteItem(str);
    updateUI();
    // Proceed with tasks->deleteItem(str) and handle any potential errors there
}


