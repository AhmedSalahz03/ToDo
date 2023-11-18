#pragma once

#ifndef MYCLASS_H
#define MYCLASS_H

using namespace std;
#include <iostream>
#include <string>
#include "ToDo.h"
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QListWidget>
#include <QCheckBox>
#include <QColor>

class ToDo;

class LinkedListNode {
private:


public:
  int key = 0;
  int priority;
  bool status;
  string value;
  LinkedListNode* next;

  LinkedListNode(int p, string v) : priority(p), value(v), next(nullptr), status(false) {
    KeyGeneration();
  }

  void KeyGeneration(){
    for (char c : value){
      key += static_cast<int>(c);
    }
  }

  int searchKeyGeneration(string Val){
    int searchKey = 0;
    for (char c : Val){
      searchKey += static_cast<int>(c);
    }
    return searchKey;
  }

};

class HashMap : public QObject {
    Q_OBJECT
private:
    static const int hashGroups = 150000;    // max size an int can carry 2147483647
    LinkedListNode** table;

public:
    HashMap() {
    table = new LinkedListNode*[hashGroups];
    for(int i = 0; i < hashGroups; i++) {
      table[i] = nullptr;
    }
  }

  ~HashMap() {
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

  void insert(int priority, string value) {
    if( priority > 5 || priority < 1){
      cout<< "you have entered wrong priority number" << endl 
      << "please enter value between 1-5"<<endl;
      return;
    }
    LinkedListNode* head;
    int key = head->searchKeyGeneration(value);
    int index = hash(key);

     head = table[index];

    LinkedListNode* prev = nullptr;
    LinkedListNode* curr = head;

    while (curr != nullptr  ) {
        if(curr->value == value){
          cout << "item already exists!" <<endl;
          return;
        }
        
      prev = curr;
      curr = curr->next;
    }
       
       LinkedListNode* node = new LinkedListNode(priority, value);
       
      if (prev == nullptr) {
        table[index] = node;
      } else {
        prev->next = node;
      } 
    
  }

   string searchItem(string value) {
    LinkedListNode* head ;
    
    int key =head->searchKeyGeneration(value);
    int index = hash(key);
    head = table[index];

    LinkedListNode* curr = head;
    while (curr != nullptr) {
      if (curr->value == value) {
        return curr->value;
      }
      curr = curr->next;
    }
    cout<<"'Not Found!" <<endl;
    return "";
  } 

  int hash(int key) {
    return key % hashGroups;
  }

 void printAll() {
  for(int j = 5 ; j>0 ; j--){
    for(int i = 0; i < hashGroups; i++) {
      LinkedListNode* head = table[i];
      
      while(head != nullptr) {
        if(head->priority == j){
        cout << "priority : "<<head->priority << " value : " << head->value << endl;
        }
        head = head->next;
      }
    }  
  }

}
 void display(QListWidget* allTasks, ToDo &todoInstance, QListWidget* completeTasks, QListWidget* incompleteTasks) {
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
                     QListWidgetItem* item = new QListWidgetItem(allTasks);
                     item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + QString::number(head->priority));
                     if (head->priority == 1) {
                         item->setForeground(darkerRed);
                     }
                     else if (head->priority == 2) {
                         item->setForeground(red);
                     }
                     if (head->status == true) {
                         item->setForeground(gray);
                     }
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
                         item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + QString::number(head->priority));
                         item->setForeground(Qt::gray);
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
                         item->setText("    " + QString::fromStdString(head->value) + "    Priorty: " + QString::number(head->priority));

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
  
void deleteItem(string value) {
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
        cout<< "key not found!";
        return;
    }

    if (prev == nullptr) { 
        // removing head node
        table[index] = curr->next;
    } else {
        prev->next = curr->next;
        curr->next = nullptr;
    }

    delete curr;
}

void updateStatus(bool stat , LinkedListNode* node){
  node->status = stat;
}

};

#endif