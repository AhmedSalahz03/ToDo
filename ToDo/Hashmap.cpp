#include "HashMap.h"
#include "ToDo.h" // Include necessary headers
#include <iostream>

// Implement the methods declared in HashMap.h

LinkedListNode::LinkedListNode(int p, std::string v) : priority(p), value(v), next(nullptr), status(false) {
    KeyGeneration();
}

void LinkedListNode::KeyGeneration() {
    for (char c : value) {
        key += static_cast<int>(c);
    }
}

int LinkedListNode::searchKeyGeneration(std::string Val) {
    int searchKey = 0;
    for (char c : Val) {
        searchKey += static_cast<int>(c);
    }
    return searchKey;
}

HashMap::HashMap() {
    table = new LinkedListNode * [hashGroups];
    for (int i = 0; i < hashGroups; i++) {
        table[i] = nullptr;
    }
}

HashMap::~HashMap() {
    for (int i = 0; i < hashGroups; i++) {
        LinkedListNode* head = table[i];
        while (head != nullptr) {
            LinkedListNode* ptr = head->next;
            delete head;
            head = ptr;
        }
    }
    delete[] table;
}

void HashMap::insert(int priority, std::string value) {
    if (priority > 5 || priority < 1) {
        std::cout << "you have entered wrong priority number" << std::endl
            << "please enter value between 1-5" << std::endl;
        return;
    }
    LinkedListNode* head;
    int key = head->searchKeyGeneration(value);
    int index = hash(key);

    head = table[index];

    LinkedListNode* prev = nullptr;
    LinkedListNode* curr = head;

    while (curr != nullptr) {
        if (curr->value == value) {
            std::cout << "item already exists!" << std::endl;
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    LinkedListNode* node = new LinkedListNode(priority, value);

    if (prev == nullptr) {
        table[index] = node;
    }
    else {
        prev->next = node;
    }
}

std::string HashMap::searchItem(std::string value) {
    LinkedListNode* head;

    int key = head->searchKeyGeneration(value);
    int index = hash(key);
    head = table[index];

    LinkedListNode* curr = head;
    while (curr != nullptr) {
        if (curr->value == value) {
            return curr->value;
        }
        curr = curr->next;
    }
    std::cout << "'Not Found!" << std::endl;
    return "";
}

int HashMap::hash(int key) {
    return key % hashGroups;
}

void HashMap::printAll() {
    for (int j = 5; j > 0; j--) {
        for (int i = 0; i < hashGroups; i++) {
            LinkedListNode* head = table[i];

            while (head != nullptr) {
                if (head->priority == j) {
                    std::cout << "priority : " << head->priority << " value : " << head->value << std::endl;
                }
                head = head->next;
            }
        }
    }
}

void HashMap::display(QListWidget* allTasks, ToDo& todoInstance, QListWidget* completeTasks, QListWidget* incompleteTasks) {
    allTasks->clear();
    completeTasks->clear();
    incompleteTasks->clear();

    QColor red = QColor(Qt::red);
    QColor darkerRed = QColor(180, 0, 0);
    QColor gray = QColor(Qt::gray);
    for (int j = 5; j > 0; j--) {
        for (int i = 0; i < hashGroups; i++) {
            LinkedListNode* head = table[i];

            while (head != nullptr) {
                if (head->priority == j) {
                    QString priorityName;
                    QListWidgetItem* item = new QListWidgetItem(allTasks);
                    if (head->priority == 1)
                        priorityName = "Very Low";
                    else if (head->priority == 2)
                        priorityName = "Low";
                    else if (head->priority == 3)
                        priorityName = "Medium";
                    else if (head->priority == 4)
                        priorityName = "High";
                    else if (head->priority == 5)
                        priorityName = "Very High";
                    item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + priorityName);
                    
                    QCheckBox* checkBox = new QCheckBox(allTasks);
                    checkBox->setChecked(head->status);
                    allTasks->setItemWidget(item, checkBox);
                    //QObject::connect(checkBox, &QCheckBox::clicked, &todoInstance, &ToDo::updateUI);
                    QObject::connect(checkBox, &QCheckBox::stateChanged, &todoInstance, &ToDo::updateUI);
                    QObject::connect(checkBox, SIGNAL(clicked()), &todoInstance, SLOT(updateUI()));
                    connect(checkBox, &QCheckBox::stateChanged, [head](int state) {
                        head->status = (state == Qt::Checked);
                        });
                }
                head = head->next;
            }
        }
    }
    for (int j = 5; j > 0; j--) {
        for (int i = 0; i < hashGroups; i++) {
            LinkedListNode* head = table[i];

            while (head != nullptr) {
                if (head->priority == j) {
                    if (head->status == true) {
                        QListWidgetItem* item = new QListWidgetItem(completeTasks);
                        QString priorityName;
                        if (head->priority == 1)
                            priorityName = "Very Low";
                        else if (head->priority == 2)
                            priorityName = "Low";
                        else if (head->priority == 3)
                            priorityName = "Medium";
                        else if (head->priority == 4)
                            priorityName = "High";
                        else if (head->priority == 5)
                            priorityName = "Very High";
                        item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + priorityName);
                        QCheckBox* checkBox = new QCheckBox(completeTasks);
                        checkBox->setChecked(head->status);
                        completeTasks->setItemWidget(item, checkBox);
                        QObject::connect(checkBox, &QCheckBox::stateChanged, &todoInstance, &ToDo::updateUI);
                        QObject::connect(checkBox, SIGNAL(clicked()), &todoInstance, SLOT(updateUI()));
                        connect(checkBox, &QCheckBox::stateChanged, [head](int state) {
                            head->status = (state == Qt::Checked);
                            });
                    }
                }
                head = head->next;
            }
        }
    }

    for (int j = 5; j > 0; j--) {
        for (int i = 0; i < hashGroups; i++) {
            LinkedListNode* head = table[i];

            while (head != nullptr) {
                if (head->priority == j) {
                    if (head->status == false) {
                        QListWidgetItem* item = new QListWidgetItem(incompleteTasks);
                        QString priorityName;
                        if (head->priority == 1)
                            priorityName = "Very Low";
                        else if (head->priority == 2)
                            priorityName = "Low";
                        else if (head->priority == 3)
                            priorityName = "Medium";
                        else if (head->priority == 4)
                            priorityName = "High";
                        else if (head->priority == 5)
                            priorityName = "Very High";
                        item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + priorityName);
 
                        QCheckBox* checkBox = new QCheckBox(incompleteTasks);
                        checkBox->setChecked(head->status);
                        incompleteTasks->setItemWidget(item, checkBox);

                        QObject::connect(checkBox, &QCheckBox::stateChanged, &todoInstance, &ToDo::updateUI);
                        QObject::connect(checkBox, SIGNAL(clicked()), &todoInstance, SLOT(updateUI()));
                        connect(checkBox, &QCheckBox::stateChanged, [head](int state) {
                            head->status = (state == Qt::Checked);
                            });
                    }
                }
                head = head->next;
            }
        }
    }
}

void HashMap::deleteItem(std::string value) {
    LinkedListNode* head = nullptr;

    int key = head->searchKeyGeneration(value);
    int index = hash(key);
    head = table[index];

    LinkedListNode* prev = nullptr;
    LinkedListNode* curr = head;

    while (curr != nullptr && curr->value != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        std::cout << "key not found!";
        return;
    }

    if (prev == nullptr) {
        // removing head node
        table[index] = curr->next;
    }
    else {
        prev->next = curr->next;
        curr->next = nullptr;
    }

    delete curr;
}

void HashMap::updateStatus(bool stat, LinkedListNode* node) {
    node->status = stat;
}
