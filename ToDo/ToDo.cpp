#include "ToDo.h"
#include "Hashmap.h"
#include <QPushButton>
#include <QLabel>
#include <qcheckbox.h>
#include "Hashmap.h"
#include <qcombobox.h>
#include <QString>
#include <string>
#include <QFile>

ToDo::ToDo(QWidget* parent)
    : QMainWindow(parent), tasks(new HashMap())
{
    ui.setupUi(this);
    QLabel* title = new QLabel(this);
    title->setText("ToDo");
    title->resize(150, 60);
    title->move(500, 20);
    QFont fontTitle = title->font();
    fontTitle.setPointSize(30);
    fontTitle.setBold(true);
    title->setFont(fontTitle);

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
    
   

    allTasks = new QListWidget(this);
    allTasks->move(100, 300);
    allTasks->resize(300, 450);

    completeTasks = new QListWidget(this);
    completeTasks->move(800, 300);
    completeTasks->resize(300, 450);

    incompleteTasks = new QListWidget(this);
    incompleteTasks->move(450, 300);
    incompleteTasks->resize(300, 450);



    deleteBtn = new QPushButton(this);
    deleteBtn->setText("Delete Task");
    deleteBtn->move(100, 200);
    deleteBtn->resize(120,40);

    connect(deleteBtn, &QPushButton::clicked, [=]() {
        deleteTask();
        });

    name = new QLineEdit(this);
    name->setPlaceholderText("Add a Todo");
    name->move(100, 100);
    name->resize(350, 40);
    name->show();

    doneButton = new QPushButton(this);
    doneButton->setText("Add Task");
    doneButton->move(620, 100);
    doneButton->resize(120, 40);

    priority = new QComboBox(this);
    priority->move(470, 100);
    priority->resize(100, 40);
    priority->setPlaceholderText("Priority");
    priority->addItem("1");
    priority->addItem("2");
    priority->addItem("3");
    priority->addItem("4");
    priority->addItem("5");

    connect(doneButton, SIGNAL(clicked()), this, SLOT(createTask()));
    
    doneButton->show();
    priority->show();

   QFile styleFile("stylesheet.qss"); 
   if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        allTasks->setStyleSheet(styleSheet);
        completeTasks->setStyleSheet(styleSheet);
        incompleteTasks->setStyleSheet(styleSheet);
        doneButton->setStyleSheet(styleSheet);
        deleteBtn->setStyleSheet(styleSheet);
        styleFile.close();
   }   
}

ToDo::~ToDo()
{}



void ToDo::createTask() {
    int selectedPriority = priority->currentIndex() + 1;
    std::string taskName = name->text().toStdString();
    Task newTask(taskName);
    tasks->insert(selectedPriority, taskName);
    name->clear();
    updateUI();
}

void ToDo::updateUI() {
    tasks->display(allTasks, *this, completeTasks, incompleteTasks);
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
void ToDo::deleteTask() {
    QListWidgetItem* selectedItemAll = allTasks->currentItem();
    QListWidgetItem* selectedItemComp = completeTasks->currentItem();
    QListWidgetItem* selectedItemIncomp = incompleteTasks->currentItem();

    if (!selectedItemAll && !selectedItemComp && !selectedItemIncomp ) {
        qDebug() << "No selected item!";
        return;
    }
  
    if (selectedItemAll) {
        QString itemText = selectedItemAll->text();
        QStringList list = itemText.split("    Priorty: ");
        QString value = list[0].trimmed();

        std::string str = value.toStdString();
        tasks->deleteItem(str);
        updateUI();
    }
    else if (selectedItemComp) {
        QString itemText = selectedItemComp->text();
        QStringList list = itemText.split("    Priorty: ");
        QString value = list[0].trimmed();

        std::string str = value.toStdString();
        tasks->deleteItem(str);
        updateUI();
    }
    else if (selectedItemIncomp) {
        QString itemText = selectedItemIncomp->text();
        QStringList list = itemText.split("    Priorty: ");
        QString value = list[0].trimmed();

        std::string str = value.toStdString();
        tasks->deleteItem(str);
        updateUI();
    }
    
}






