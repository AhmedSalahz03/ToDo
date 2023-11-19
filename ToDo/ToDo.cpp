#include "ToDo.h"
#include "Hashmap.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include "Hashmap.h"
#include <QtWidgets/QComboBox>
#include <QtCore/QString>
#include <string>
#include <QtCore/QFile>
#include <qmessagebox.h>


ToDo::ToDo(QWidget* parent)
    : QMainWindow(parent), tasks(new HashMap())
{
    // Title
    ui.setupUi(this);
    QLabel* title = new QLabel(this);
    title->setText("ToDo");
    title->resize(150, 60);
    title->move(500, 20);
    QFont fontTitle = title->font();
    fontTitle.setPointSize(30);
    fontTitle.setBold(true);
    title->setFont(fontTitle);
    // All Tasks Label
    QLabel* allTasksLabel = new QLabel(this);
    allTasksLabel->setText("All Tasks");
    allTasksLabel->resize(150, 23);
    allTasksLabel->move(100, 268);
    QFont font = allTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    allTasksLabel->setFont(font);
    // Complete Tasks Label
    QLabel* completeTasksLabel = new QLabel(this);
    completeTasksLabel->setText("Complete Tasks");
    completeTasksLabel->resize(250, 23);
    completeTasksLabel->move(800, 268);
    font = completeTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    completeTasksLabel->setFont(font);
    // Incomplete Tasks Label
    QLabel* incompleteTasksLabel = new QLabel(this);
    incompleteTasksLabel->setText("Incomplete Tasks");
    incompleteTasksLabel->resize(250,23);
    incompleteTasksLabel->move(450, 268);
    font = incompleteTasksLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    incompleteTasksLabel->setFont(font);
    
    // All Tasks Widget
    allTasks = new QListWidget(this);
    allTasks->move(100, 300);
    allTasks->resize(300, 450);
    // Complete Tasks Widget
    completeTasks = new QListWidget(this);
    completeTasks->move(800, 300);
    completeTasks->resize(300, 450);
    completeTasks->setSelectionMode(QAbstractItemView::NoSelection);
    // Incomplete Tasks Widget
    incompleteTasks = new QListWidget(this);
    incompleteTasks->move(450, 300);
    incompleteTasks->resize(300, 450);
    incompleteTasks->setSelectionMode(QAbstractItemView::NoSelection);

    // Delete Task Button
    deleteBtn = new QPushButton(this);
    deleteBtn->setText("Delete Task");
    deleteBtn->move(270, 262);
    deleteBtn->resize(110,30);
    deleteBtn->setToolTip("Select a ToDo Task to delete");
    connect(deleteBtn, &QPushButton::clicked, [=]() {
        deleteTask();
        });
    
    // Add a ToDo Line Edit
    name = new QLineEdit(this);
    name->setPlaceholderText("Add a Todo");
    name->move(100, 100);
    name->resize(350, 40);
    name->show();
    // Add Task Button
    doneButton = new QPushButton(this);
    doneButton->setText("Add Task");
    doneButton->move(620, 100);
    doneButton->resize(120, 40);
    doneButton->setToolTip("Add the Task to the Todo List");
    connect(doneButton, SIGNAL(clicked()), this, SLOT(createTask()));
    // Priority ComboBox
    priority = new QComboBox(this);
    priority->move(470, 100);
    priority->resize(100, 40);
    priority->setPlaceholderText("Priority");
    priority->addItem("Very Low");
    priority->addItem("Low");
    priority->addItem("Meduim");
    priority->addItem("High");
    priority->addItem("Very High");
    priority->setToolTip("Select the Task's Priority");
    
    // Search QLineEdit
    searchedTask = new QLineEdit(this);
    searchedTask->setPlaceholderText("Search for a Todo");
    searchedTask->move(100, 200);
    searchedTask->resize(350, 40);
    searchedTask->show();
    // Search Button
    searchButton = new QPushButton(this);
    searchButton->setText("Search");
    searchButton->move(470, 200);
    searchButton->resize(120, 40);
    searchButton->setToolTip("Search for a Task");
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchTask()));

    // Show Button and ComboBox
    doneButton->show();
    priority->show();

    // Connect the Stylesheet File
    QFile styleFile("stylesheet.qss"); 
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
      
        QString styleSheet = QLatin1String(styleFile.readAll());
        allTasks->setStyleSheet(styleSheet);
        completeTasks->setStyleSheet(styleSheet);
        incompleteTasks->setStyleSheet(styleSheet);
        doneButton->setStyleSheet(styleSheet);
        deleteBtn->setStyleSheet(styleSheet);
        searchButton->setStyleSheet(styleSheet);
        styleFile.close();
                
    }   

}

ToDo::~ToDo()
{}

void ToDo::createTask() {
    int selectedPriority = priority->currentIndex() + 1;
    std::string taskName = name->text().toStdString();
    if (taskName == "") {
        QMessageBox::warning(this, "Empty Task", "Add ToDo Field must be Filled");
        return;
    }
    if (selectedPriority < 1) {
        QMessageBox::warning(this, "No Priority Selected", "Please select a priority!");
        return;
    }
    tasks->insert(selectedPriority, taskName);
    name->clear();
    updateUI();
}

void ToDo::updateUI() {

    tasks->display(allTasks, *this, completeTasks, incompleteTasks);

}

void ToDo::deleteTask() {

    QListWidgetItem* selectedItemAll = allTasks->currentItem();

    if (!selectedItemAll) {
        qDebug() << "No selected item!";
        return;
    }
    
    QString itemText = selectedItemAll->text();
    QStringList list = itemText.split("    Priorty: ");
    QString value = list[0].trimmed();
    std::string str = value.toStdString();
    tasks->deleteItem(str);
    updateUI();
       
}

void ToDo::searchTask() {
    std::string searchedTaskStr = searchedTask->text().toStdString();
    if (searchedTask->text() == "") {
        QMessageBox::warning(this, "Empty Field", "Search Field is Empty");
        return;
    }
    std::string returnedSearchValue = tasks->searchItem(searchedTaskStr);
    if (returnedSearchValue == "") {
        QMessageBox::warning(this, "Not Found", "Task not found");
        return;
    }

    for (int i = 0; i < allTasks->count(); ++i) {
        QListWidgetItem* currentItem = allTasks->item(i);
        
        if (currentItem) {
            QString itemText = currentItem->text();
            QStringList list = itemText.split("    Priorty: ");
            QString value = list[0].trimmed();
            std::string str = value.toStdString();

            if (str == returnedSearchValue) {
                allTasks->setCurrentItem(currentItem);
                return;
            }
        }
    }
    
    return;
   
}







