#pragma once

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
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
    std::string value;
    LinkedListNode* next;

    LinkedListNode(int p, std::string v);
    void KeyGeneration();
    int searchKeyGeneration(std::string Val);
};

class HashMap : public QObject {
    Q_OBJECT
private:
    static const int hashGroups = 150000; // max size an int can carry 2147483647
    LinkedListNode** table;

public:
    HashMap();
    ~HashMap();

    void insert(int priority, std::string value);
    std::string searchItem(std::string value);
    int hash(int key);
    void printAll();
    void display(QListWidget* allTasks, ToDo& todoInstance, QListWidget* completeTasks, QListWidget* incompleteTasks);
    void deleteItem(std::string value);
    void updateStatus(bool stat, LinkedListNode* node);
};

#endif
