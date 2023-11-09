#pragma once

#ifndef MYCLASS_H
#define MYCLASS_H

using namespace std;
#include <iostream>
#include <string>
#include "ToDo.h"
#include <QPushButton>
#include <QLabel>
#include <qcheckbox.h>
#include <QObject>
#include <QListWidget>
#include <QCheckBox>

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

class HashMap {
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
 void updateUI(QListWidget* listWidget) {
     listWidget->clear();
     

     for (int j = 5; j > 0; j--) {
         for (int i = 0; i < hashGroups; i++) {
             LinkedListNode* head = table[i];

             while (head != nullptr) {
                 if (head->priority == j) {
                     QListWidgetItem* item = new QListWidgetItem(listWidget);
                     item->setText(QString::fromStdString(head->value));

                     QCheckBox* checkBox = new QCheckBox(listWidget);
                     checkBox->setChecked(head->status);
                     listWidget->setItemWidget(item, checkBox);

                     
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